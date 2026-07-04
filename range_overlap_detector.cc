#include "range_overlap_detector.h"

#include <cstddef>

#include "absl/log/check.h"

// Compare first on start being less
// ..then on length being *longer*
// ..then on the name.
bool operator<(const Range& lhs, const Range& rhs) {
  if (lhs.start < rhs.start) {
    return true;
  } else if (lhs.start > rhs.start) {
    return false;
  } else if (lhs.length > rhs.length) {
    return true;
  } else if (lhs.length < rhs.length) {
    return false;
  } else if (lhs.name < rhs.name) {
    return true;
  } else if (lhs.name > rhs.name) {
    return false;
  }
  return false;
}

bool Range::ValueInRange(size_t val) const {
  return ((val >= start) && (val < (start + length)));
}

bool Range::OverlapsWith(const Range& other) const {
  return this->ValueInRange(other.start) || other.ValueInRange(this->start);
}

RangeOverlapDetector& RangeOverlapDetector::AddRange(const Range& range) {
  ranges_.push_back(range);
  return *this;
}

bool RangeOverlapDetector::HasOverlappingRanges() {
  if (ranges_.size() < 2) {
    // Shortcut: if the detector has zero or one range, there can't be an
    // overlap by definition.
    return false;
  }
  // Start by sorting the ranges as defined by the Range operator<,
  // which ensures that ranges are sorted first by start, but then
  // by LONGEST range.
  std::sort(ranges_.begin(), ranges_.end());

  // Initialize 'max' to hold the range we've observed that has the largest
  // max byte. Initialize 'curr' to the following range after that.
  auto max = ranges_.begin();
  auto curr = ranges_.begin();
  ++curr;

  // This should be a hard check. We should never encounter a situation where
  // ranges_ contains fewer than two items at this point, since we checked for
  // degenerate conditions at the start of the function.
  CHECK(curr != ranges_.end()) << "ranges_ should contain at least two items";

  // Algorithm: Check to see if the start of 'curr' is strictly outside the
  // range of the max range we've seen. If not, return 'true' indicating
  // overlap. Otherwise continue until all ranges are observed.
  for (; curr != ranges_.end(); ++curr) {
    if (curr->start < (max->start + max->length)) {
      return true;
    }
    if ((curr->start + curr->length) > (max->start + max->length)) {
      max = curr;
    }
  }

  return false;
}
