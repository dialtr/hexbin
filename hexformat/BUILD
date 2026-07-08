load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

cc_library(
  visibility = [ "//visibility:public" ],
  name = "binary",
  hdrs = [
    "binary.h",
  ],
  srcs = [
    "binary.cc"
  ],
  deps = [
    "@abseil-cpp//absl/status:status",
    "@abseil-cpp//absl/status:statusor",
  ],
)

cc_library(
  visibility = [ "//visibility:public" ],
  name = "checksum",
  hdrs = [
    "checksum.h",
  ],
  srcs = [
    "checksum.cc",
  ]
)

cc_library(
  visibility = [ "//visibility:public" ],
  name = "range_overlap_detector",
  hdrs = [
    "range_overlap_detector.h",
  ],
  srcs = [
    "range_overlap_detector.cc",
  ],
  deps = [
    "@abseil-cpp//absl/log:check",
  ],
)

cc_library(
  visibility = [ "//visibility:public" ],
  name = "record",
  hdrs = [
    "record.h",
  ],
  srcs = [
    "record.cc",
  ],
  deps = [
    "@abseil-cpp//absl/status:status",
    "@abseil-cpp//absl/status:statusor",
    ":checksum",
    ":utility",
  ],
)

cc_library(
  visibility = [ "//visibility:public" ],
  name = "utility",
  hdrs = [
    "utility.h",
  ],
  srcs = [
    "utility.cc",
  ],
  deps = [
    "@abseil-cpp//absl/status:status",
    "@abseil-cpp//absl/status:statusor",
  ],
)

cc_library(
  visibility = [ "//visibility:public" ],
  name = "hexformat",
  hdrs = [
  ],
  srcs = [],
  deps = [
    "@abseil-cpp//absl/status:status",
    "@abseil-cpp//absl/status:statusor",
    "@abseil-cpp//absl/strings",
    "@abseil-cpp//absl/log:check",
    ":binary",
    ":checksum",
    ":range_overlap_detector",
    ":record",
    ":utility",
  ],
)

cc_test(
  name = "checksum_test",
  srcs = ["checksum_test.cc"],
  deps = [
    "@abseil-cpp//absl/log:check",
    "@abseil-cpp//absl/status:status",
    "@googletest//:gtest_main",
    ":checksum",
  ],
  timeout = "short",
)

cc_test(
  name = "range_overlap_detector_test",
  srcs = ["range_overlap_detector_test.cc"],
  deps = [
    "@abseil-cpp//absl/log:check",
    "@abseil-cpp//absl/status:status",
    "@googletest//:gtest_main",
    ":range_overlap_detector",
  ],
  timeout = "short",
)

cc_test(
  name = "record_test",
  srcs = ["record_test.cc"],
  deps = [
    "@abseil-cpp//absl/log:check",
    "@abseil-cpp//absl/status:status",
    "@googletest//:gtest_main",
    ":record",
  ],
  timeout = "short",
)

cc_test(
  name = "utility_test",
  srcs = ["utility_test.cc"],
  deps = [
    "@abseil-cpp//absl/log:check",
    "@abseil-cpp//absl/status:status",
    "@googletest//:gtest_main",
    ":utility",
  ],
  timeout = "short",
)
