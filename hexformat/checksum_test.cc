// Copyright (C) 2026 The hexbin authors. All rights reserved.
#include "hexformat/checksum.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include "absl/status/status.h"

TEST(Checksum, Constructor) {
  Checksum c;
  EXPECT_EQ(0, c.value());
}

TEST(Checksum, SingleByteHasCorrectChecksum) {
  Checksum c;
  const uint8_t byte = 0x1;
  c.AppendByte(byte);
  const uint8_t expected = -byte;
  EXPECT_EQ(expected, c.value());
}

TEST(Checksum, VectorHasCorrectChecksum) {
  Checksum c;
  const std::vector<uint8_t> v{0x1, 0x2, 0x3};
  c.AppendData(v);
  const uint8_t expected = -(0x1 + 0x2 + 0x3);
  EXPECT_EQ(expected, c.value());
}

TEST(Checksum, VectorHasCorrectChecksumOverflow) {
  Checksum c;
  const std::vector<uint8_t> v{0xcc, 0xdd, 0xee};
  c.AppendData(v);
  size_t sum = 0;
  sum += 0xcc;
  sum += 0xdd;
  sum += 0xee;
  sum %= 256;
  const uint8_t expected = -static_cast<uint8_t>(sum);
  EXPECT_EQ(expected, c.value());
}
