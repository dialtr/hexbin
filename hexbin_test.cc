#include "hexbin.h"

#include <gtest/gtest.h>

TEST(HexCharToNybble, InvalidCharReturnsError) {
  EXPECT_EQ(HexCharToNybble('T'), kInvalidHexChar);
}
