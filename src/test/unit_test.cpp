#include "gtest/gtest.h"

#include "../foo.h"

TEST(Foo, times)
{
  EXPECT_EQ(Foo(4).times(4), 16);
}

TEST(Foo, isPositive)
{
  EXPECT_TRUE(Foo(4).isPositive());
}
