load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

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
	  name = "hexformat",
	  hdrs = [
			  "binary.h",
				"record.h",
				"stream_utility.h",
	  ],
	  srcs = [
			  "binary.cc",
				"record.cc",
				"stream_utility.cc",
	  ],
	  deps = [
			  "@abseil-cpp//absl/status:status",
		    "@abseil-cpp//absl/status:statusor",
	      "@abseil-cpp//absl/strings",
		    "@abseil-cpp//absl/log:check",
				":checksum",
				":range_overlap_detector",
	  ],
)

cc_test(
	  name = "hexformat_test",
		srcs = ["hexformat_test.cc"],
		deps = [
				"@googletest//:gtest_main",
			  ":checksum",
		    ":hexformat",
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

