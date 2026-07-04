#include "record.h"

#include <cstdint>
#include <vector>

#include "absl/status/status.h"
#include "stream_utility.h"

/*
absl::Status ConsumeStartChar(std::istream& input);
absl::StatusOr<uint8_t> ConsumeHexByte(std::istream& input);
*/

absl::StatusOr<Record> Record::Read(std::istream& input) {
  // Read the start character, ':'.
  absl::Status status = ConsumeStartByte(input);
  if (!status.ok()) {
    return status;
  }

  // The next component of a record is the byte count (rep'd as a byte).
  absl::StatusOr<uint8_t> byte_count = ConsumeHexByte(input);
  if (!byte_count.ok()) {
    return byte_count.status();
  }

  // The next two bytes comprise the address offset of the data.
  unsigned short address = 0;
  for (int i = 0; i < 2; ++i) {
    absl::StatusOr<uint8_t> part = ConsumeHexByte(input);
    if (!part.ok()) {
      return part.status();
    }
    address <<= 8;
    address |= part.value();
  }

  // The next byte is the record type.
  absl::StatusOr<uint8_t> record_type = ConsumeHexByte(input);
  if (!record_type.ok()) {
    return record_type.status();
  }

  // What follows are 'count' bytes.
  std::vector<uint8_t> data;
  const int count = static_cast<int>(byte_count.value());
  for (int i = 0; i < count; ++i) {
    absl::StatusOr<uint8_t> byte = ConsumeHexByte(input);
    if (!byte.ok()) {
      return byte.status();
    }
    data.push_back(byte.value());
  }

  // Finally, a checksum is provided.
  absl::StatusOr<uint8_t> checksum = ConsumeHexByte(input);
  if (!checksum.ok()) {
    return checksum.status();
  }

  return absl::OkStatus();
}
