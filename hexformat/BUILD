load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

cc_library(
	  visibility = [ "//visibility:public" ],
	  name = "hexformat",
	  hdrs = [
			  "binary.h",
			  "checksum.h",
				"hex_record.h",
				"range_overlap_detector.h",
				"stream_utility.h",
	  ],
	  srcs = [
			  "binary.cc",
			  "checksum.cc",
				"hex_record.cc",
				"range_overlap_detector.cc",
				"stream_utility.cc",
	  ],
	  deps = [
			  "@abseil-cpp//absl/status:status",
		    "@abseil-cpp//absl/status:statusor",
	      "@abseil-cpp//absl/strings",
		    "@abseil-cpp//absl/log:check",
	  ],
)

cc_test(
	  name = "hexformat_test",
		srcs = ["hexformat_test.cc"],
		deps = [
		    ":hexformat",
				"@googletest//:gtest_main",
		],
		timeout = "short",
)

