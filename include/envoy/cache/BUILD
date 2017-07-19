licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "cache_interface",
    hdrs = ["cache.h"],
    deps = [
        "//include/envoy/http:header_map_interface",
    ],
)
