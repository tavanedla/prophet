load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_proto_grpc_cpp//:defs.bzl", "cpp_proto_library", "cpp_grpc_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "services_proto",
    srcs = ["services.proto"],
)

cpp_proto_library(
    name = "services_cpp_proto",
    protos = [":services_proto"],
)

cpp_grpc_library(
    name = "services_cc_grpc",
    protos = [":services_proto"],
)

cc_library(
    name = "event_logger",
    hdrs = ["event_logger.h"],
    deps = [
        ":logging",
        ":services_cc_grpc",
    ],
)

cc_library(
    name = "event_processor",
    srcs = ["event_processor.cc"],
    hdrs = ["event_processor.h"],
    deps = [
        ":suspicious_users",
        ":suspicious_ips",
        ":services_cc_grpc",
        ":event_logger",
    ]
)

cc_library(
    name = "logging",
    hdrs = ["logging.h"],
    deps = [],
)

cc_library(
    name = "suspicious_ips",
    hdrs = ["suspicious_ips.h"],
    srcs = ["suspicious_ips.cc"],
    deps = [
        "//data_structures:ip_ranges",
        "//data_structures:string_set",
    ]
)

cc_library(
    name = "suspicious_users",
    hdrs = ["suspicious_users.h"],
    srcs = ["suspicious_users.cc"],
    deps = [
        "//data_structures:string_set",
    ]
)

cc_library(
    name = "suspicious_events_reader",
    hdrs = ["suspicious_events_reader.h"],
    deps = [
        ":services_cc_grpc",
        ":logging",
    ]
)