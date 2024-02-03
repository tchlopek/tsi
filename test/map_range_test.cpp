#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

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
