#ifndef STREAM_UTILITY_H_
#define STREAM_UTILITY_H_

#include <istream>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

// Consume characters from the stream until the start character ':' is read.
//   Returns absl::OkStatus() on success.
//   Returns absl::ResourceExhaustedError() if EOF is reached before reading the
//   char.
absl::Status ConsumeStartByte(std::istream& input);

// Consume two hexadecimal characters from the stream in succession that
// code a single unsigned char (byte).
//   Returns unsigned char on success.
//   Returns absl::InvalidArgumentError if a non-hex char is read.
//   Returns absl::ResourceExhaustedError if EOF is reached.
absl::StatusOr<unsigned char> ConsumeHexByte(std::istream& input);

const unsigned char kInvalidHexChar = 0x80;

// Convert a hexadecimal char to nybble. The nybble is stored in the
// lower 4 bites of the unsigned char. If the character is not a valid
// hex char, the function returns kInvalidHexChar.
unsigned char HexCharToNybble(char ch);

#endif  // STREAM_UTILITY_H_
