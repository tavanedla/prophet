package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ip_ranges",
    hdrs = ["ip_ranges.h"],
    srcs = ["ip_ranges.cc"],
    deps = [
        ":trie",
        "//libs:logging",
    ]
)

cc_test(
    name = "ip_ranges_test",
    srcs = ["ip_ranges_test.cc"],
    deps = [
        ":ip_ranges",
        "//googletest:gtest",
        "//googletest:gtest_main",
    ]
)

cc_library(
    name = "string_set",
    hdrs = ["string_set.h"],
    srcs = ["string_set.cc"],
    deps = [
        "//libs:logging",
    ],
)

cc_library(
    name = "trie",
    hdrs = ["trie.h"],
    srcs = ["trie.cc"],
    deps = [],
)