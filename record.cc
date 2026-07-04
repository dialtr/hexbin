#include "record.h"

#include "absl/status/status.h"
#include "stream_utility.h"

absl::StatusOr<Record> Record::Read(std::istream& input) {
  return absl::OkStatus();
}
