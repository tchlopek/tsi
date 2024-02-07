#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

class AllTest : public Test {
public:
  std::vector<int> vec{ 1, 2, 3, 4, 5 };
};

TEST_F(AllTest, AllReturnsTrueWhenPredicateIsTrueForAllElements) {
  EXPECT_TRUE(iter(vec).all([](int el) { return el > 0; }));
}

TEST_F(AllTest, AllReturnsFalseWhenPredicateIsFalseForAnyElement) {
  EXPECT_FALSE(iter(vec).all([](int el) { return el < 5; }));
}
