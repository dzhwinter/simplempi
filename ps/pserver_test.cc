#include <gtest/gtest.h>
#include "pserver.h"

using namespace ps;

TEST(Pserver, Init) {
  Pserver<int64_t, float> pserver;
}
