#include "hexbin.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(HexCharToNybble, InvalidCharReturnsError) {
  EXPECT_EQ(HexCharToNybble('T'), kInvalidHexChar);
}

TEST(HexCharToNybble, AllValidCharactersWork) {
  const char hexchars[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
                           'A', 'B', 'C', 'D', 'E', 'F'};
  const int hexchars_len = sizeof(hexchars) / sizeof(hexchars[0]);
  const unsigned char nybbles[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
      0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  const int nybbles_len = sizeof(nybbles) / sizeof(nybbles[0]);
  EXPECT_EQ(hexchars_len, nybbles_len);
  for (int i = 0; i < hexchars_len; ++i) {
    EXPECT_EQ(nybbles[i], HexCharToNybble(hexchars[i]));
  }
}
