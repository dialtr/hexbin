#ifndef STREAM_UTILITY_H_
#define STREAM_UTILITY_H_

#include <istream>

#include "absl/status/status.h"

// Consume characters from the stream until the start character ':' is read.
//   Returns absl::OkStatus() on success.
//   Returns absl::OutOfRangeError() if EOF is reached before reading the char.
absl::Status ConsumeStartChar(std::istream& input);

const unsigned char kInvalidHexChar = 0x80;

// Convert a hexadecimal char to nybble. The nybble is stored in the
// lower 4 bites of the unsigned char. If the character is not a valid
// hex char, the function returns kInvalidHexChar.
unsigned char HexCharToNybble(char ch);

#endif  // STREAM_UTILITY_H_
