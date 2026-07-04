#ifndef STREAM_UTILITY_H_
#define STREAM_UTILITY_H_

#include <istream>

#include "absl/status/status.h"

// Consume characters from the stream until the start character ':' is read.
//   Returns absl::OkStatus() on success.
//   Returns absl::OutOfRangeError() if EOF is reached before reading the char.
absl::Status ConsumeStartChar(std::istream& input);

#endif  // STREAM_UTILITY_H_
