#pragma once
#include <stdint.h>
#include <typeindex>

namespace ps {
/**
 * @brief a multi-device allocator
 */
template <typename Place>
void* Alloc(size_t size);

template <typename Place>
void Free();

template <typename Place>
struct PoDDeleter {
  void operator()(void* p) const { delete p; }
};
}
