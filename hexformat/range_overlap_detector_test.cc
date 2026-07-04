// Copyright (C) 2026 The hexbin authors. All rights reserved.
#include "hexformat/range_overlap_detector.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <sstream>

#include "absl/status/status.h"

TEST(RangeOverlapDetector, DegenerateRangeTest) {
  RangeOverlapDetector d;
  EXPECT_FALSE(d.HasOverlappingRanges());
}

TEST(RangeOverlapDetector, SingleRangeTest) {
  RangeOverlapDetector d;
  Range range;
  range.start = 0;
  range.length = 10;
  d.AddRange(range);
  EXPECT_FALSE(d.HasOverlappingRanges());
}

TEST(RangeOverlapDetector, TwoRangesNoOverlap) {
  RangeOverlapDetector d;
  Range a{.start{0}, .length{10}};
  d.AddRange(a);
  Range b{.start{10}, .length{10}};
  d.AddRange(b);
  EXPECT_FALSE(d.HasOverlappingRanges());
}

TEST(RangeOverlapDetector, TwoRangesOverlap) {
  RangeOverlapDetector d;
  Range a{.start{0}, .length{10}};
  d.AddRange(a);
  Range b{.start{9}, .length{10}};
  d.AddRange(b);
  EXPECT_TRUE(d.HasOverlappingRanges());
}

TEST(RangeOverlapDetector, OverlapWithin) {
  RangeOverlapDetector d;
  Range a{.start{0}, .length{10}};
  d.AddRange(a);
  Range b{.start{2}, .length{4}};
  d.AddRange(b);
  EXPECT_TRUE(d.HasOverlappingRanges());
}

TEST(RangeOverlapDetector, DisjointOverlap) {
  RangeOverlapDetector d;
  Range a{.start{0}, .length{100}};
  d.AddRange(a);
  Range b{.start{150}, .length{100}};
  d.AddRange(b);
  Range c{.start{110}, .length{50}};
  d.AddRange(c);
  EXPECT_TRUE(d.HasOverlappingRanges());
}
