#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <sstream>

#include "absl/status/status.h"
#include "record.h"
#include "stream_utility.h"

TEST(HexCharToNybble, InvalidCharReturnsError) {
  EXPECT_EQ(HexCharToNybble('T'), kInvalidHexChar);
}

TEST(HexCharToNybble, AllValidCharactersWork) {
  const char hexchars[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
                           'A', 'B', 'C', 'D', 'E', 'F'};
  const int hexchars_len = sizeof(hexchars) / sizeof(hexchars[0]);
  const uint8_t nybbles[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                             0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                             0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  const int nybbles_len = sizeof(nybbles) / sizeof(nybbles[0]);
  EXPECT_EQ(hexchars_len, nybbles_len);
  for (int i = 0; i < hexchars_len; ++i) {
    EXPECT_EQ(nybbles[i], HexCharToNybble(hexchars[i]));
  }
}

TEST(ConsumeStartByte, ConsumesCorrectly) {
  std::stringstream ss("    :abc");
  absl::Status status = ConsumeStartByte(ss);
  EXPECT_EQ(absl::OkStatus(), status);
  const int next = ss.get();
  EXPECT_EQ('a', next);
}

TEST(ConsumeStartByte, ReturnsResourceExhaustedWhenNoStartFound) {
  std::stringstream ss("abc");
  absl::Status status = ConsumeStartByte(ss);
  EXPECT_EQ(absl::StatusCode::kResourceExhausted, status.code());
}

TEST(ConsumeStartByte, ReturnsResourceExhaustedEmptyStream) {
  std::stringstream ss("");
  absl::Status status = ConsumeStartByte(ss);
  EXPECT_EQ(absl::StatusCode::kResourceExhausted, status.code());
}

// absl::StatusOr<uint8_t> ConsumeHexByte(std::istream& input);

TEST(ConsumeHexByte, ConsumesCorrectly) {
  std::stringstream ss("ab");
  auto status_or_val = ConsumeHexByte(ss);
  EXPECT_TRUE(status_or_val.ok());
  EXPECT_EQ(0xab, status_or_val.value());
}

TEST(ConsumeHexByte, ReturnsResourceExhaustedAtEof) {
  std::stringstream ss("");
  auto status_or_val = ConsumeHexByte(ss);
  EXPECT_EQ(absl::StatusCode::kResourceExhausted,
            status_or_val.status().code());
}

TEST(ConsumeHexByte, ReturnsInvalidArgumentOnBadChar) {
  std::stringstream ss("ax");
  auto status_or_val = ConsumeHexByte(ss);
  EXPECT_EQ(absl::StatusCode::kInvalidArgument, status_or_val.status().code());
}
