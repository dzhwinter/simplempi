#include "place.h"
#include "gtest/gtest.h"

using namespace ps;

TEST(Place, Type) {
  int i;
  float f;
  double d;
  EXPECT_EQ(SizeofType(i), sizeof(i));
  EXPECT_EQ(SizeofType(f), sizeof(f));
  EXPECT_EQ(SizeofType(d), sizeof(d));
}

TEST(Place, CPUGPU) {
  CPUPlace pa;
  GPUPlace pb;
  EXPECT_EQ(is_gpu_place(pb), true);
  EXPECT_EQ(is_cpu_place(pa), true);

  Place place = GPUPlace(1);
  EXPECT_EQ(is_gpu_place(boost::get<GPUPlace>(place)), true);
}
