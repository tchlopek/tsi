#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

class ReverseRangeForRandomAccessTest : public Test {
public:
  std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(ReverseRangeForRandomAccessTest, ReversedRangeHasOppositeOrderOfElements) {
  ASSERT_THAT(iter(v).reverse(), ElementsAre(5, 4, 3, 2, 1));
}

TEST_F(
  ReverseRangeForRandomAccessTest,
  DoublyReversedRangeHasSameOrderOfElements
) {
  ASSERT_THAT(iter(v).reverse().reverse(), ElementsAreArray(v));
}

TEST_F(ReverseRangeForRandomAccessTest, EmptyTest) {
  ASSERT_THAT(iter(std::vector<int>{}).reverse(), IsEmpty());
}
