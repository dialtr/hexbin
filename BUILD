load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

cc_binary(
  name = "hexbin",
  srcs = ["main.cc"],
  deps = [
    "@abseil-cpp//absl/flags:flag",
    "@abseil-cpp//absl/flags:parse",
    "//hexformat",
  ],
)
