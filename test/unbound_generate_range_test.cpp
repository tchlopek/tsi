#include <vector>

#include <tsi/gen.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::gen;

TEST(UnboundGenerateRangeTest, IteratorsAreNeverEqual) {
  auto g = gen(0);
  EXPECT_NE(g.begin(), g.begin());
  EXPECT_NE(g.end(), g.end());
}

TEST(UnboundGenerateRangeTest, IsNeverEmpty) {
  EXPECT_FALSE(gen(0).empty());
}

TEST(UnboundGenerateRangeTest, GenerateValuesInAscendingOrder) {
  EXPECT_THAT(gen(0).take(5), ElementsAre(0, 1, 2, 3, 4));
}

TEST(UnboundGenerateRangeTest, CanIterateOverArrays) {
  std::vector v{ 'a', 's', 'd' };
  EXPECT_THAT(gen(v.data()).take(v.size()), ElementsAre(&v[0], &v[1], &v[2]));
}

TEST(UnboundGenerateRangeTest, CanIterateOverArraysWithDeref) {
  std::vector v{ 'a', 'r', 'r', 'a', 'y' };
  EXPECT_THAT(
    gen(v.data()).take(v.size()).deref(),
    ElementsAre('a', 'r', 'r', 'a', 'y')
  );
}
