#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

static int to_int(int a) {
  return a;
}

class MapRangeForRandomAccessTest : public Test {
public:
  std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(MapRangeForRandomAccessTest, NumbersAreSquared) {
  ASSERT_THAT(
    iter(v).map([](int v) { return v * v; }),
    ElementsAre(1, 4, 9, 16, 25)
  );
}

TEST_F(MapRangeForRandomAccessTest, EmptyTest) {
  ASSERT_THAT(
    iter(std::vector<int>{}).map([](int v) { return v * v; }),
    IsEmpty()
  );
}

TEST_F(MapRangeForRandomAccessTest, FunctionPointerTest) {
  ASSERT_THAT(iter(v).map(to_int), ElementsAreArray(v));
}
