#include <forward_list>
#include <list>
#include <vector>

#include <cppiter/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using cppiter::iter;

using Containers = testing::
  Types<std::vector<int>, std::list<int>, std::forward_list<int>>;

template<typename T>
class SkipRangeTest : public Test {
public:
  T v{ 1, 2, 3, 4, 5 };
};

TYPED_TEST_SUITE(SkipRangeTest, Containers);

TYPED_TEST(SkipRangeTest, SkipReturnsTwoLastElements) {
  ASSERT_THAT(iter(this->v).skip(3), ElementsAre(4, 5));
}

TYPED_TEST(SkipRangeTest, ExceededSkipReturnsEmptyRange) {
  ASSERT_THAT(iter(this->v).skip(6), IsEmpty());
}

TYPED_TEST(SkipRangeTest, SkipZeroReturnsSourceRange) {
  ASSERT_THAT(iter(this->v).skip(0), ElementsAreArray(this->v));
}

TYPED_TEST(SkipRangeTest, EmptyTest) {
  ASSERT_THAT(iter(TypeParam{}).skip(10), IsEmpty());
}