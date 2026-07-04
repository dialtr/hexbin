// Copyright (C) 2026 The hexbin authors. All rights reserved.
#ifndef HEXFORMAT_RECORD_H_
#define HEXFORMAT_RECORD_H_

#include <cstdint>
#include <iostream>
#include <vector>

#include "absl/status/statusor.h"

class Record {
 public:
  enum RecordType {
    kDataRecord = 0x00,
    kEndOfFile = 0x01,
    kExtendedSegmentAddress = 0x02,
    kStartSegmentAddress = 0x03,
    kExtendedLinearAddress = 0x04,
    kStartLinearAddress = 0x05
  };

  // Read options: default is to validate checksum.
  struct ReadOptions {
    bool validate_checksum = true;
  };

  // Read a single record from the stream.
  static absl::StatusOr<Record> Read(std::istream& input,
                                     const ReadOptions& options);

  // Validate the checksum.
  bool IsChecksumValid() const;
  bool IsEof() const { return record_type_ == kEndOfFile; }

  // Accessors
  int byte_count() const { return byte_count_; }
  uint16_t address() const { return address_; }
  uint8_t record_type() const { return record_type_; }
  const std::vector<uint8_t>& data() const { return data_; }
  uint8_t provided_checksum() const { return provided_checksum_; }
  uint8_t calculated_checksum() const { return calculated_checksum_; }

 private:
  Record(int byte_count, uint16_t address, uint8_t record_type,
         std::vector<uint8_t> data, uint8_t provided_checksum,
         uint8_t calculated_checksum);

  int byte_count_ = 0;
  uint16_t address_ = 0;
  uint8_t record_type_ = kEndOfFile;
  std::vector<uint8_t> data_;
  uint8_t provided_checksum_ = 0;
  uint8_t calculated_checksum_ = 0;
};

#endif  // HEXFORMAT_RECORD_H_
