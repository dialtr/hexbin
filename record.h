#ifndef RECORD_H_
#define RECORD_H_

#include <cstdint>
#include <iostream>
#include <vector>

#include "absl/status/statusor.h"

class Record {
 public:
  enum class RecordType : uint8_t {
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

 private:
  int byte_count_ = 0;
  unsigned short address_ = 0;
  RecordType record_type_ = RecordType::kEndOfFile;
  std::vector<uint8_t> data_;
  uint8_t checksum_ = 0;
};

#endif  // RECORD_H_
