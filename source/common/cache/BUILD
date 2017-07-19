licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "cache_constants",
    hdrs = ["cache_constants.h"],
)

envoy_cc_library(
    name = "ufesorch_lib",
    srcs = ["cache_impl.cc"],
    hdrs = ["cache_impl.h"],
    deps = [
         ":cache_constants",
        "//include/envoy/cache:cache_interface",
        "//include/envoy/upstream:cluster_manager_interface",
        "//source/common/http:message_lib",
        "//source/common/http:utility_lib",
        "//source/common/common:enum_to_int",
        "//source/common/common:logger_lib",
    ],
)
