#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

namespace {

bool isValue2Or3(int v) {
  return v == 2 || v == 3;
}

template<typename val>
auto eq(val v) {
  return [v](const auto& old) {
    return old == v;
  };
}
}    // namespace

class ReplaceRangeForRandomAccessTest : public Test {
public:
  std::vector<int> v{ 4, 2, 3, 4, 5 };
};

TEST_F(ReplaceRangeForRandomAccessTest, ReplacedElementsUsingPredicate) {
  ASSERT_THAT(iter(v).replace(isValue2Or3, 20), ElementsAre(4, 20, 20, 4, 5));
}

TEST_F(ReplaceRangeForRandomAccessTest, ElementsReplacedUsingValueMatcher) {
  ASSERT_THAT(iter(v).replace(eq(4), 7), ElementsAre(7, 2, 3, 7, 5));
}

TEST_F(ReplaceRangeForRandomAccessTest, EmptyTest) {
  ASSERT_THAT(iter(std::vector<int>{}).replace(eq(0), 1), IsEmpty());
}
