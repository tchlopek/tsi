#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <iter.hpp>

#include "matcher.hpp"

using namespace testing;
using cppiter::iter;

class EnumerateRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 3, 4, 1, 8, 1 };
};

TEST_F(EnumerateRangeForRandomAccessTest, ElementsAreNumeratedFromOne) {
    ASSERT_THAT(iter(v).enumerate(1), ElementsAre(
        Pair(1, 3), Pair(2, 4), Pair(3, 1), Pair(4, 8), Pair(5, 1)
    ));
}

TEST_F(EnumerateRangeForRandomAccessTest, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).enumerate(), utest::IsEmpty());
}
