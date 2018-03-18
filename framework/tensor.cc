#include "tensor.h"
#include <cstring>  // memcpy
// cudamemcpy

namespace ps {
/**
 *  @brief 4 kinds of Tensor Copy
 *  CPU -> CPU
 *  CPU -> GPU
 *  GPU -> CPU
 *  GPU -> GPU
 */

void TensorCopy(const Tensor& src, Place place, Tensor* dst) {
  dst->Resize(src.Shape());
  dst->mutable_data(place, src.Type());
}
}
