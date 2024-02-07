#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

class AnyTest : public Test {
public:
  std::vector<int> vec{ 1, 2, 3, 4, 5 };
};

TEST_F(AnyTest, AnyReturnsTrueWhenPredicateIsTrueForAnyElement) {
  EXPECT_TRUE(iter(vec).any([](int el) { return el == 1; }));
}

TEST_F(AnyTest, AnyReturnsFalseWhenPredicateIsTrueForNoneElement) {
  EXPECT_FALSE(iter(vec).any([](int el) { return el < 0; }));
}
