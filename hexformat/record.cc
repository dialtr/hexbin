// Copyright (C) 2026 The hexbin authors. All rights reserved.
#include "hexformat/record.h"

#include <iostream>
#include <utility>
#include <vector>

#include "absl/status/status.h"
#include "hexformat/checksum.h"
#include "hexformat/utility.h"

using std::cerr;
using std::cout;
using std::endl;

Record::Record(int byte_count, uint16_t address, uint8_t record_type,
               std::vector<uint8_t> data, uint8_t provided_checksum,
               uint8_t calculated_checksum)
    : byte_count_(byte_count),
      address_(address),
      record_type_(record_type),
      data_(std::move(data)),
      provided_checksum_(provided_checksum),
      calculated_checksum_(calculated_checksum) {}

absl::StatusOr<Record> Record::Read(std::istream& input,
                                    const ReadOptions& read_options) {
  // Read the start character, ':'.
  absl::Status status = ConsumeStartByte(input);
  if (!status.ok()) {
    return status;
  }

  // All bytes read are part of the calculated checksum, except for
  // the start character, which is always ':' and considered out of band.
  Checksum calc_checksum;

  // The next component of a record is the byte count (rep'd as a byte).
  absl::StatusOr<uint8_t> byte_count = ConsumeHexByte(input);
  if (!byte_count.ok()) {
    return byte_count.status();
  }
  calc_checksum.AppendByte(byte_count.value());

  // The next two bytes comprise the address offset of the data.
  uint16_t address = 0;
  for (int i = 0; i < 2; ++i) {
    absl::StatusOr<uint8_t> part = ConsumeHexByte(input);
    if (!part.ok()) {
      return part.status();
    }
    calc_checksum.AppendByte(part.value());
    address <<= 8;
    address |= part.value();
  }

  // The next byte is the record type.
  absl::StatusOr<uint8_t> record_type = ConsumeHexByte(input);
  if (!record_type.ok()) {
    return record_type.status();
  }
  calc_checksum.AppendByte(record_type.value());

  // What follows are 'count' bytes.
  std::vector<uint8_t> data;
  const int count = static_cast<int>(byte_count.value());
  for (int i = 0; i < count; ++i) {
    absl::StatusOr<uint8_t> byte = ConsumeHexByte(input);
    if (!byte.ok()) {
      return byte.status();
    }
    calc_checksum.AppendByte(byte.value());
    data.push_back(byte.value());
  }

  // Finally, a checksum is provided.
  absl::StatusOr<uint8_t> provided_checksum = ConsumeHexByte(input);
  if (!provided_checksum.ok()) {
    return provided_checksum.status();
  }

  // If the caller wanted to validate checksums, check the provided
  // checksum against our calculated value. Any discrepancy is
  // considered a data loss error.
  if (read_options.validate_checksum) {
    if (provided_checksum.value() != calc_checksum.value()) {
      return absl::DataLossError("the checksum for the record was not valid");
    }
  }

  return Record(byte_count.value(), address, record_type.value(),
                std::move(data), provided_checksum.value(),
                calc_checksum.value());
}

bool Record::IsValidChecksum() const {
  return (provided_checksum_ == calculated_checksum_);
}
