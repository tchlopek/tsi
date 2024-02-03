#include <forward_list>
#include <list>
#include <vector>

#include <tsi/range/view_range.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

using Containers = testing::
  Types<std::vector<int>, std::list<int>, std::forward_list<int>>;

template<typename T>
class ViewRangeTest : public Test {
public:
  T v{ 1, 2, 3, 4, 5 };

  auto get_view() {
    return tsi::rng::view_range{ v.begin(), v.end() };
  }
};

TYPED_TEST_SUITE(ViewRangeTest, Containers);

TYPED_TEST(ViewRangeTest, ViewRangeCanTraverseOverPairOfIterators) {
  ASSERT_THAT(this->get_view(), ElementsAreArray(this->v));
}
