cmake_minimum_required(VERSION 3.0)
project(paddle CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(external/zlib)    # download, build, install python
include(external/gflags)    # download, build, install gflags
include(external/glog)      # download, build, install glog
include(external/gtest)     # download, build, install gtest
include(external/protobuf)  # download, build, install protobuf
# include(external/python)    # download, build, install python

include(generic)            # simplify cmake module
include(cpplint)            # set paddle c++ style

set(THIRD_PARTY_PATH "${CMAKE_BINARY_DIR}/third_party" CACHE STRING
  "A path setting third party libraries download & build directories.")

# options
option(WITH_TESTING     "Compile with unit testing"        ON)


set(EXTERNAL_LIBS
    ${GFLAGS_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${GLOG_LIBRARIES}
    ${PROTOBUF_LIBRARY}
    ${PYTHON_LIBRARIES}
)
add_subdirectory(ps)
