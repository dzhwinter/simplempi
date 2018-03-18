#pragma once
#include <glog/logging.h>
#include <stdint.h>
#include <stdlib.h>  // posix_memalign
#include <typeindex>
#include "place.h"

namespace ps {

constexpr static size_t ALIGN_SIZE = 4096UL;
/**
 * @brief a multi-device allocator
 */
template <typename Place>
void* Alloc(size_t size);

template <>
void* Alloc<CPUPlace>(size_t size) {
  size_t remain = size % ALIGN_SIZE;
  size_t alloc_size = size + ALIGN_SIZE - remain;
  void* p = nullptr;
  posix_memalign(&p, ALIGN_SIZE, alloc_size);
  VLOG(5) << "Alloc CPU pointer: " << p;
  return p;
}

template <typename Place>
void Free(void* p);

template <>
void Free<CPUPlace>(void* p) {
  if (p != nullptr) {
    free(p);
    p = nullptr;
    VLOG(5) << "Free CPU pointer: " << p;
  }
}

template <typename T, typename Place>
struct PoDDeleter {
  void operator()(T* p) const { Free<Place>(p); }
};
}
