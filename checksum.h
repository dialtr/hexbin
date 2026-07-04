// Copyright (C) 2026 The hexbin authors. All rights reserved.
#ifndef CHECKSUM_H_
#define CHECKSUM_H_

// Calculate the twos-complement checksum of a stream of bytes.

#include <cstdint>
#include <vector>

class Checksum {
 public:
  Checksum() : sum_(0) {}

  // Append a single byte.
  Checksum& AppendByte(const uint8_t byte);

  // Append data.
  Checksum& AppendData(const std::vector<uint8_t>& data);

  // Return checksum value.
  uint8_t value() const;

 private:
  uint8_t sum_ = 0;
};

#endif  // CHECKSUM_H_
