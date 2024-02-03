#include <deque>
#include <list>
#include <set>
#include <vector>

#include <tsi/gen.hpp>
#include <tsi/iter.hpp>

#include <gtest/gtest.h>

using namespace testing;
using tsi::gen;
using tsi::iter;

TEST(CollectTest, ElementsCanBeCollectedIntoSomeOtherContainerType) {
  std::list<int> exp{ 48, 49, 50 };
  EXPECT_EQ(
    iter(std::vector<char>{ '0', '1', '2' }).collect<std::list<int>>(),
    exp
  );
}

TEST(CollectTest, ElementsCanBeCollectedToAutoDeducedContainerType) {
  std::set<unsigned long long> exp{ 1, 2, 3 };
  EXPECT_EQ(iter(std::vector{ 1ull, 2ull, 3ull }).collect<std::set>(), exp);
}

TEST(CollectTest, GeneratedValuesCanBeColletedToContainerTemplate) {
  std::deque exp{ 2, 4, 6 };
  EXPECT_EQ(gen(2).step(2).take(3).collect<std::deque>(), exp);
}