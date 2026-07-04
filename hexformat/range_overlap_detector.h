// Copyright (C) 2026 The hexbin authors. All rights reserved.
#ifndef HEXFORMAT_RANGE_OVERLAP_DETECTOR_H_
#define HEXFORMAT_RANGE_OVERLAP_DETECTOR_H_

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

class Range {
 public:
  std::string name = "";
  size_t start = 0;
  size_t length = 0;

  bool ValueInRange(size_t value) const;
  bool OverlapsWith(const Range& other) const;
};

// Custom comparison. Note: best practice would be to implement <=>
// as of C++20. However, due to the strict ordering that we want for
// the algorithm, we implement this traditionally.
bool operator<(const Range& lhs, const Range& rhs);

class RangeOverlapDetector {
 public:
  // Default ctors, dtor OK.

  // Add a range for consideration.
  RangeOverlapDetector& AddRange(const Range& range);

  // Return 'true' if any of the ranges overlap.
  bool HasOverlappingRanges();

 private:
  std::vector<Range> ranges_;
};

#endif  // HEXFORMAT_RANGE_OVERLAP_DETECTOR_H_
