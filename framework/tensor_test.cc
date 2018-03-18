#include "tensor.h"
#include "gtest/gtest.h"

TEST(Tensor, CPUTensor) {
  Tensor t, g;
  CPUPlace place;
  t.Resize({2, 3});
  int* t_data = t.mutable_data<int>(place);
  int* g_data = g.mutable_data<int>({2, 3}, place);
  for (int i = 0; i < 2 * 3; ++i) {
    t_data[i] = i;
    g_data[i] = i;
  }
}

TEST(Tensor, GPUTensor) {
  Tensor t, g;
  GPUPlace place;
  t.Resize({2, 3});
  // Need Kernel Here
  int* t_data = t.mutable_data<int>(place);
  int* g_data = g.mutable_data<int>({2, 3}, place);
}
