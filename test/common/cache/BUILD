licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_test",
    "envoy_package",
)

envoy_package()

envoy_cc_test(
    name = "cache_impl_test",
    srcs = ["cache_impl_test.cc"],
    deps = [
        "//source/common/http:header_map_lib",
        "//source/common/http:headers_lib",
        "//source/common/cache:cache_lib",
        "//source/common/http:message_lib",
        "//test/mocks/http:http_mocks",
        "//test/mocks/upstream:upstream_mocks",
        "//test/test_common:utility_lib",
    ],
)
