#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <forward_list>
#include <list>
#include <vector>

#include <cppiter/iter.hpp>

using namespace testing;
using cppiter::iter;

using Containers = testing::Types<
    std::vector<int>,
    std::list<int>,
    std::forward_list<int>>;

template<typename T>
class TakeRangeTest : public Test {
public:
    T v{ 1, 2, 3, 4, 5 };
};

TYPED_TEST_SUITE(TakeRangeTest, Containers);

TYPED_TEST(TakeRangeTest, TakeHasOnlyThreeElements) {
    ASSERT_THAT(iter(this->v).take(3), ElementsAre(1, 2, 3));
}

TYPED_TEST(TakeRangeTest, ExceededTakeReturnSourceRange) {
    ASSERT_THAT(iter(this->v).take(10), ElementsAreArray(this->v));
}

TYPED_TEST(TakeRangeTest, TakeIsEmpty) {
    ASSERT_THAT(iter(this->v).take(0), IsEmpty());
}

TYPED_TEST(TakeRangeTest, EmptyTest) {
    ASSERT_THAT(iter(TypeParam{}).take(10), IsEmpty());
}
