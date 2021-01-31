#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <list>
#include <forward_list>

#include <filter_range.hpp>

using namespace testing;

namespace {

bool odd(int e) {
    return e % 2 == 1;
}

bool divisibleBy3(int e) {
    return e % 3 == 0;
}

}

class FilterRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
};

TEST_F(FilterRangeForRandomAccessTest, FilteredNumbersAreOdd) {
    ASSERT_THAT(filter(v, odd), ElementsAre(1, 3, 5, 7, 9));
}

TEST_F(FilterRangeForRandomAccessTest, FilterDivisibleBy3AfterFilterOdd) {
    ASSERT_THAT(filter(filter(v, odd), divisibleBy3), ElementsAre(3, 9));
}
