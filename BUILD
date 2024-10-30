
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "prophet_server",
    srcs = ["server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//libs:services_cc_grpc",
        "//libs:suspicious_ips",
        "//libs:suspicious_events_reader",
        "//libs:suspicious_users",
        "//libs:event_logger",
        "//libs:event_processor",
    ],
)

