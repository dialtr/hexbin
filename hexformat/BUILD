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
	  name = "hexformat",
	  hdrs = [
			  "binary.h",
				"record.h",
				"range_overlap_detector.h",
				"stream_utility.h",
	  ],
	  srcs = [
			  "binary.cc",
				"record.cc",
				"range_overlap_detector.cc",
				"stream_utility.cc",
	  ],
	  deps = [
			  "@abseil-cpp//absl/status:status",
		    "@abseil-cpp//absl/status:statusor",
	      "@abseil-cpp//absl/strings",
		    "@abseil-cpp//absl/log:check",
				":checksum",
	  ],
)

cc_test(
	  name = "hexformat_test",
		srcs = ["hexformat_test.cc"],
		deps = [
			  ":checksum",
		    ":hexformat",
				"@googletest//:gtest_main",
		],
		timeout = "short",
)

