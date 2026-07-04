#ifndef RECORD_H_
#define RECORD_H_

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

  // Read a record from the stream.
  // Returns record, or error.
  static absl::StatusOr<Record> Read(std::istream& input);

  // Validate the checksum.
  bool IsValidChecksum() const;
  bool IsEof() const { return record_type_ == kEndOfFile; }

  // Accessors
  int byte_count() const { return byte_count_; }
  uint16_t address() const { return address_; }
  uint8_t record_type() const { return record_type_; }
  const std::vector<uint8_t>& data() const { return data_; }
  uint8_t provided_checksum() const { return provided_checksum_; }

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

#endif  // RECORD_H_
