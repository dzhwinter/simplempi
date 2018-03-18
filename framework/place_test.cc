#include "place.h"
#include "gtest/gtest.h"

TEST(SizeofType, Type) {
  int i, float f, double d;
  EXPECT_EQ(SizeofType(i), sizeof(i));
  EXPECT_EQ(SizeofType(f), sizeof(f));
  EXPECT_EQ(SizeofType(d), sizeof(d));
}
