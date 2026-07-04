load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

cc_library(
	  name = "hexbin_lib",
	  hdrs = [
			  "checksum.h",
				"hex_record.h",
				"stream_utility.h",
	  ],
	  srcs = [
			  "checksum.cc",
				"hex_record.cc",
				"stream_utility.cc",
	  ],
	  deps = [
			  "@abseil-cpp//absl/status:status",
		    "@abseil-cpp//absl/status:statusor",
	      "@abseil-cpp//absl/strings",
		    "@abseil-cpp//absl/log:check",
	  ],
)

cc_binary(
	  name = "hexbin",
	  srcs = ["main.cc"],
	  deps = [
		    ":hexbin_lib",
				"@abseil-cpp//absl/flags:flag",
				"@abseil-cpp//absl/flags:parse",
		],
)

cc_test(
	  name = "hexbin_test",
		srcs = ["hexbin_test.cc"],
		deps = [
		    ":hexbin_lib",
				"@googletest//:gtest_main",
		],
		timeout = "short",
)

