#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <cppiter/iter.hpp>

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
    EXPECT_THAT(range(v.begin(), v.end()), ElementsAre(v.begin(), v.begin() + 1, v.begin() + 2));
}

TEST(BoundGenerateRangeTest, CanIterateOverArraysWithDeref) {
    std::vector v{ 'a', 'r', 'r', 'a', 'y' };
    EXPECT_THAT(range(v.begin(), v.end()).deref(), ElementsAre('a', 'r', 'r', 'a', 'y'));
}
