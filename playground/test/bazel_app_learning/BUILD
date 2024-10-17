# BUILD

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_google_protobuf//:protobuf.bzl", "cc_proto_library")

proto_library(
    name = "message_proto",
    srcs = ["proto/message.proto"],
)

# cc_proto_library(
#     name = "message_cc_proto",
#     deps = [":message_proto"],
# )

cc_binary(
    name = "my_app",
    srcs = ["main.cpp"],
    deps = [":message_proto"],
)
