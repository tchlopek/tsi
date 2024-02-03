#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

class ReduceTest : public Test {
public:
  std::vector<int> vec{ 1, 2, 3, 4, 5 };
};

TEST_F(ReduceTest, ReduceAccumulatesElements) {
  ASSERT_THAT(iter(vec).reduce(std::plus{}), Optional(15));
}

TEST_F(ReduceTest, ReduceReturnEmptyOptOnEmptyRange) {
  ASSERT_EQ(iter(std::vector<int>{}).reduce(std::plus{}), std::nullopt);
}
