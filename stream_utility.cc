#include "stream_utility.h"

#include <istream>

#include "absl/status/status.h"

absl::Status ConsumeStartChar(std::istream& input) {
  for (;;) {
    int c = input.get();
    if (c == std::char_traits<char>::eof()) {
      return absl::OutOfRangeError("reached the end of the input stream");
    }
    if (c == ':') {
      // This is the "Start char".
      break;
    }
  }
  return absl::OkStatus();
}
