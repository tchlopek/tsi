#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

class FoldTest : public Test {
public:
  std::vector<int> vec{ 1, 2, 3, 4, 5 };
};

TEST_F(FoldTest, FoldAccumulatesElements) {
  ASSERT_EQ(iter(vec).fold(0, std::plus{}), 15);
}
