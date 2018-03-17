#pragma once
#include <boost/variant.hpp>

namespace ps {

// place indicate the memory address space
struct CPUPlace {};

struct GPUPlace {
  GPUPlace() : gpu_id(0) {}
  int gpu_id;
};

typedef boost::variant<CPUPlace, GPUPlace> Place;
}
