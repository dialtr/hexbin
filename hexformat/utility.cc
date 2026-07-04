// Copyright (C) 2026 The hexbin authors. All rights reserved.
#include "hexformat/utility.h"

#include <cctype>
#include <cstdint>
#include <istream>
#include <string>

#include "absl/status/status.h"

absl::Status ConsumeStartByte(std::istream& input) {
  for (;;) {
    int c = input.get();
    if (c == std::char_traits<char>::eof()) {
      return absl::ResourceExhaustedError(
          "reached the end of the input stream before reading start char");
    }
    if (c == ':') {
      // This is the "Start char".
      break;
    }
  }
  return absl::OkStatus();
}

absl::StatusOr<uint8_t> ConsumeHexByte(std::istream& input) {
  uint8_t byte = 0;
  for (int i = 0; i < 2; ++i) {
    const int c = input.get();
    if (c == std::char_traits<char>::eof()) {
      return absl::ResourceExhaustedError(
          "reached the end of the input stream before reading hex char");
    }
    const uint8_t nybble = HexCharToNybble(static_cast<char>(c));
    if (nybble == kInvalidHexChar) {
      return absl::InvalidArgumentError(
          "read an invalid character (not a hex chat)");
    }
    byte <<= 4;
    byte |= nybble;
  }
  return byte;
}

uint8_t HexCharToNybble(char ch) {
  switch (toupper(ch)) {
    case '0':
      return 0x0;
    case '1':
      return 0x1;
    case '2':
      return 0x2;
    case '3':
      return 0x3;
    case '4':
      return 0x4;
    case '5':
      return 0x5;
    case '6':
      return 0x6;
    case '7':
      return 0x7;
    case '8':
      return 0x8;
    case '9':
      return 0x9;
    case 'A':
      return 0xa;
    case 'B':
      return 0xb;
    case 'C':
      return 0xc;
    case 'D':
      return 0xd;
    case 'E':
      return 0xe;
    case 'F':
      return 0xf;
    default:
      return kInvalidHexChar;
  }
}
