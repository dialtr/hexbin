#include <gtest/gtest.h>
#include "hexbin.h"

TEST(toolkit, Add) {
  int result = Add(1, 2);
  EXPECT_EQ(result, 3);
}

