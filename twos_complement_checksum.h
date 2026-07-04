#ifndef TWOS_COMPLEMENT_CHECKSUM_H_
#define TWOS_COMPLEMENT_CHECKSUM_H_

#include <cstdint>
#include <vector>

class TwosComplementChecksum {
 public:
  TwosComplementChecksum() : sum_(0) {}

  // Append data.
  TwosComplementChecksum& AppendData(const std::vector<uint8_t>& data);

  // Append a single byte.
  TwosComplementChecksum& AppendByte(const uint8_t byte);

  // Return checksum value.
  uint8_t value() const;

 private:
  uint8_t sum_ = 0;
};

#endif  // TWOS_COMPLEMENT_CHECKSUM_H_
