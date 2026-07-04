// Copyright (C) 2026 The hexbin authors. All rights reserved.
#include "checksum.h"

#include <cstdint>
#include <vector>

Checksum& Checksum::AppendData(const std::vector<uint8_t>& data) {
  for (auto byte : data) {
    sum_ += byte;
  }
  return *this;
}

Checksum& Checksum::AppendByte(const uint8_t byte) {
  sum_ += byte;
  return *this;
}

uint8_t Checksum::value() const { return -sum_; }
