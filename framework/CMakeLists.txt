cc_library(tensor SRCS tensor.cc)
cc_test(tensor_test SRCS tensor_test.cc DEPS tensor)
cc_test(place_test SRCS place_test.cc)
