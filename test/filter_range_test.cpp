#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

namespace {

bool odd(int e) {
  return e % 2 == 1;
}

}    // namespace

class FilterRangeForRandomAccessTest : public Test {
public:
  std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
};

TEST_F(FilterRangeForRandomAccessTest, FilteredNumbersAreOdd) {
  ASSERT_THAT(iter(v).filter(odd), ElementsAre(1, 3, 5, 7, 9));
}

TEST_F(FilterRangeForRandomAccessTest, ReverseFilteredNumbersAreOdd) {
  ASSERT_THAT(iter(v).filter(odd).reverse(), ElementsAre(9, 7, 5, 3, 1));
}

TEST_F(FilterRangeForRandomAccessTest, EmptySourceRangeIsEmpty) {
  ASSERT_THAT(iter(std::vector<int>{}).filter(odd), IsEmpty());
}

TEST_F(FilterRangeForRandomAccessTest, NoneElementsFilteredIsEmpty) {
  ASSERT_THAT(iter(std::vector<int>{ 2, 4, 6 }).filter(odd), IsEmpty());
}
