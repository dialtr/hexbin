#include "twos_complement_checksum.h"

#include <cstdint>
#include <vector>

TwosComplementChecksum& TwosComplementChecksum::AppendData(
    const std::vector<uint8_t>& data) {
  for (auto byte : data) {
    sum_ += byte;
  }
  return *this;
}

TwosComplementChecksum& TwosComplementChecksum::AppendByte(const uint8_t byte) {
  sum_ += byte;
  return *this;
}

uint8_t TwosComplementChecksum::value() const { return -sum_; }
