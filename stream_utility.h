// Copyright (C) 2026 The hexbin authors. All rights reserved.
#ifndef STREAM_UTILITY_H_
#define STREAM_UTILITY_H_

#include <cstdint>
#include <istream>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

// Consume characters from the stream until the start character ':' is read.
//   Returns absl::OkStatus() on success.
//   Returns absl::ResourceExhaustedError() if EOF is reached before reading the
//   char.
absl::Status ConsumeStartByte(std::istream& input);

// Consume two hexadecimal characters from the stream in succession that
// code a single uint8_t (byte).
//   Returns uint8_t on success.
//   Returns absl::InvalidArgumentError if a non-hex char is read.
//   Returns absl::ResourceExhaustedError if EOF is reached.
absl::StatusOr<uint8_t> ConsumeHexByte(std::istream& input);

const uint8_t kInvalidHexChar = 0x80;

// Convert a hexadecimal char to nybble. The nybble is stored in the
// lower 4 bites of the uint8_t. If the character is not a valid
// hex char, the function returns kInvalidHexChar.
uint8_t HexCharToNybble(char ch);

#endif  // STREAM_UTILITY_H_
