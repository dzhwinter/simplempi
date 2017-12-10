proto_library(service_proto SRCS service.proto)
cc_test(pserver_test SRCS pserver_test.cc DEPS brpc service_proto protobuf)
