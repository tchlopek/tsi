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
class StrideRangeTest : public Test {
public:
    T v{ 1, 2, 3, 4, 5 };
};

TYPED_TEST_SUITE(StrideRangeTest, Containers);

TYPED_TEST(StrideRangeTest, StrideShouldIterateOverEverySecondElement) {
    ASSERT_THAT(iter(this->v).stride(2), ElementsAre(1, 3, 5));
}

TYPED_TEST(StrideRangeTest, StrideShouldIterateOverEveryThirdElement) {
    ASSERT_THAT(iter(this->v).stride(3), ElementsAre(1, 4));
}

TYPED_TEST(StrideRangeTest, ExceededStrideReturnsFirstElement) {
    ASSERT_THAT(iter(this->v).stride(10), ElementsAre(1));
}

TYPED_TEST(StrideRangeTest, EmptyTest) {
    ASSERT_THAT(iter(TypeParam{}).stride(3), IsEmpty());
}
