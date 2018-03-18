#pragma once
#include <glog/logging.h>
#include <boost/variant.hpp>
#include <typeindex>
#include <typeinfo>

namespace ps {

template <typename... T>
struct SizeofTypeImpl;

template <typename T>
struct SizeofTypeImpl<T> {
  int operator()(std::type_index type) const {
    if (typeid(T).hash_code() == type.hash_code()) {
      return sizeof(T);
    } else {
      return 0;
    }
  }
};

template <>
struct SizeofTypeImpl<> {
  int operator()(std::type_index type) const { return 0; }
};

template <typename HEAD, typename... TAIL>
struct SizeofTypeImpl<HEAD, TAIL...> {
  int operator()(std::type_index type) const {
    SizeofTypeImpl<HEAD> functor;
    int size = functor(type);
    if (size != 0) {
      return size;
    } else {
      SizeofTypeImpl<TAIL...> tail;
      return tail(type);
    }
  }
};

static inline int SizeofType(std::type_index type) {
  SizeofTypeImpl<char, int, float, double> functor;
  int size = functor(type);
  CHECK(size != 0) << "Unsupported type " << type.name();
  return size;
}

// place indicate the memory address space
struct CPUPlace {};

struct GPUPlace {
  GPUPlace() : gpu_id(0) {}
  int gpu_id;
};

typedef boost::variant<CPUPlace, GPUPlace> Place;
constexpr static int CPUPlaceIndex = 0;
constexpr static int GPUPlaceIndex = 0;

class PlaceVisitor : public boost::static_visitor<int> {
public:
  int operator()(const CPUPlace& place) const { return CPUPlaceIndex; }
  int operator()(const GPUPlace& place) const { return GPUPlaceIndex; }
};

static inline bool is_gpu_place(const Place& place) {
  return boost::apply_visitor(PlaceVisitor(), place) == GPUPlaceIndex;
}

static inline bool is_cpu_place(const Place& place) {
  return boost::apply_visitor(PlaceVisitor(), place) == CPUPlaceIndex;
}

}  // namespace ps
