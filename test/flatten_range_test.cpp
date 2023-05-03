#include <forward_list>
#include <list>
#include <vector>

#include <cppiter/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using cppiter::iter;
using Containers = testing::Types<
  std::vector<std::vector<std::vector<int>>>,
  std::list<std::vector<std::list<int>>>,
  std::list<std::list<std::forward_list<int>>>>;

template<typename T>
class FlattenRangeTest : public Test {
public:
  // clang-format off
  T nestedContainer {
    {
        {},
        {}
    },
    {
        { 1 }
    },
    {},
    {
        { 2, 3 },
        { 4 },
        {}
    },
    {
        {}
    },
    {
        { 5, 6 }
    },
    {
        {}
    }
  };
  // clang-format on
};

TYPED_TEST_SUITE(FlattenRangeTest, Containers);

TYPED_TEST(FlattenRangeTest, shouldIterateOverNestedElements) {
  ASSERT_THAT(
    iter(this->nestedContainer).flatten().flatten(),
    ElementsAre(1, 2, 3, 4, 5, 6)
  );
}
