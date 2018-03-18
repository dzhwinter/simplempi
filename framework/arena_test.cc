#include "arena.h"
#include <memory>
#include "gtest/gtest.h"

using namespace ps;

TEST(Arena, CPU) {
  CPUPlace place;
  for (size_t size = 1; size <= 1e6; size *= 10) {
    int* data = static_cast<int*>(Alloc<CPUPlace>(size));
    Free<CPUPlace>(static_cast<void*>(data));
  }
}

TEST(Arena, unique_ptr) {
  CPUPlace place;
  size_t size = 1e4;
  std::unique_ptr<uint8_t> p(static_cast<uint8_t*>(Alloc<CPUPlace>(size)),
                             PoDDeleter<uint8_t, CPUPlace>());
}
