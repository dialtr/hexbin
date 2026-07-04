load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

cc_library(
	  name = "hexbin_lib",
	  hdrs = [
        "hexbin.h"
	  ],
	  srcs = [
		    "hexbin.cc"
	  ],
	  deps = [
		    "@abseil-cpp//absl/status:statusor",
	      "@abseil-cpp//absl/strings",
		    "@abseil-cpp//absl/log:check",
	  ],
)

cc_binary(
	  name = "hexbin",
	  srcs = ["main.cc"],
	  deps = [":hexbin_lib"],
)

cc_test(
	  name = "hexbin_test",
		srcs = ["hexbin_test.cc"],
		deps = [
		    ":hexbin_lib",
				"@googletest//:gtest_main",
		],
)

