#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <iter.hpp>

#include "matcher.hpp"

using namespace testing;
using cppiter::iter;

class TakeRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(TakeRangeForRandomAccessTest, TakeHasOnlyThreeElements) {
    ASSERT_THAT(iter(v).take(3), ElementsAre(1, 2, 3));
}

TEST_F(TakeRangeForRandomAccessTest, TakeIsEmpty) {
    ASSERT_THAT(iter(v).take(0), utest::IsEmpty());
}

TEST_F(TakeRangeForRandomAccessTest, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).take(10), utest::IsEmpty());
}
