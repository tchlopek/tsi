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
class StepRangeTest : public Test {
public:
  T v{ 1, 2, 3, 4, 5 };
};

TYPED_TEST_SUITE(StepRangeTest, Containers);

TYPED_TEST(StepRangeTest, StepShouldIterateOverEverySecondElement) {
  ASSERT_THAT(iter(this->v).step(2), ElementsAre(1, 3, 5));
}

TYPED_TEST(StepRangeTest, StepShouldIterateOverEveryThirdElement) {
  ASSERT_THAT(iter(this->v).step(3), ElementsAre(1, 4));
}

TYPED_TEST(StepRangeTest, ExceededStepReturnsFirstElement) {
  ASSERT_THAT(iter(this->v).step(10), ElementsAre(1));
}

TYPED_TEST(StepRangeTest, EmptyTest) {
  ASSERT_THAT(iter(TypeParam{}).step(3), IsEmpty());
}

TEST(StepRangeTestList, StepShouldIterateOverEveryThirdElementRevesed) {
  EXPECT_THAT(
    iter(std::vector<int>{ 1, 2, 3, 4, 5 }).step(3).reverse(),
    ElementsAre(4, 1)
  );
  EXPECT_THAT(
    iter(std::vector<int>{ 1, 2, 3, 4, 5 }).reverse().step(3),
    ElementsAre(5, 2)
  );
}
