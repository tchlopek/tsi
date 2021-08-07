#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <cppiter/iter.hpp>

using namespace testing;
using cppiter::gen;

TEST(GenerateRangeTest, IteratorsAreNeverEqual) {
    auto g = gen(0);
    EXPECT_NE(g.begin(), g.begin());
    EXPECT_NE(g.end(), g.end());
}

TEST(GenerateRangeTest, IsNeverEmpty) {
    EXPECT_FALSE(gen(0).empty());
}

TEST(GenerateRangeTest, GenerateValuesInAscendingOrder) {
    EXPECT_THAT(gen(0).take(5), ElementsAre(0, 1, 2, 3, 4));
}

TEST(GenerateRangeTest, GenerateValuesInDescendingOrder) {
    EXPECT_THAT(gen(5).take(5).reverse(), ElementsAre(4, 3, 2, 1, 0));
}

TEST(GenerateRangeTest, CanIterateOverArrays) {
    std::vector v{ 'a', 's', 'd' };
    EXPECT_THAT(gen(v.data()).take(v.size()), ElementsAre(&v[0], &v[1], &v[2]));
}

TEST(GenerateRangeTest, CanIterateOverArraysWithDeref) {
    std::vector v{ 'a', 'r', 'r', 'a', 'y' };
    EXPECT_THAT(gen(v.data()).take(v.size()).deref(), ElementsAre('a', 'r', 'r', 'a', 'y'));
}
