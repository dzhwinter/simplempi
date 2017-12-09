proto_library(service_proto SRCS service.proto)
cc_test(pserver_test SRCS pserver_test.cc DEPS service_proto)
