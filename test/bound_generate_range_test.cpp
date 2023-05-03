#include <functional>
#include <vector>

#include <cppiter/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using cppiter::range;

TEST(BoundGenerateRangeTest, IsEmptyForTheSameBeginAndEndValues) {
  EXPECT_THAT(range(0, 0), IsEmpty());
}

TEST(BoundGenerateRangeTest, GenerateValuesInAscendingOrder) {
  EXPECT_THAT(range(0, 5), ElementsAre(0, 1, 2, 3, 4));
}

TEST(BoundGenerateRangeTest, GenerateValuesInDescendingOrder) {
  EXPECT_THAT(range(0, 5).reverse(), ElementsAre(4, 3, 2, 1, 0));
}

TEST(BoundGenerateRangeTest, CanIterateOverArrays) {
  std::vector v{ 'a', 's', 'd' };
  EXPECT_THAT(
    range(v.begin(), v.end()),
    ElementsAre(v.begin(), v.begin() + 1, v.begin() + 2)
  );
}

TEST(BoundGenerateRangeTest, CanIterateOverArraysWithDeref) {
  std::vector v{ 'a', 'r', 'r', 'a', 'y' };
  EXPECT_THAT(
    range(v.begin(), v.end()).deref(),
    ElementsAre('a', 'r', 'r', 'a', 'y')
  );
}

using I = cppiter::rng::iter::bound_generate_iterator<int>;

struct BoundGenerateIteratorsRelationalOperatorTest
  : public TestWithParam<std::tuple<std::function<bool(I, I)>, int, int, bool>> {
};

TEST_P(BoundGenerateIteratorsRelationalOperatorTest, run) {
  auto r = range(0, 5);
  const auto [comp, offset1, offset2, result] = GetParam();
  EXPECT_EQ(comp(r.begin() + offset1, r.begin() + offset2), result);
}

INSTANTIATE_TEST_SUITE_P(
  run,
  BoundGenerateIteratorsRelationalOperatorTest,
  Values(
    std::tuple{ std::less<>{}, 0, 0, false },
    std::tuple{ std::less<>{}, 1, 0, false },
    std::tuple{ std::less<>{}, 0, 1, true },
    std::tuple{ std::greater<>{}, 0, 0, false },
    std::tuple{ std::greater<>{}, 1, 0, true },
    std::tuple{ std::greater<>{}, 0, 1, false },
    std::tuple{ std::less_equal<>{}, 0, 0, true },
    std::tuple{ std::less_equal<>{}, 1, 0, false },
    std::tuple{ std::less_equal<>{}, 0, 1, true },
    std::tuple{ std::greater_equal<>{}, 0, 0, true },
    std::tuple{ std::greater_equal<>{}, 1, 0, true },
    std::tuple{ std::greater_equal<>{}, 0, 1, false }
  )
);
