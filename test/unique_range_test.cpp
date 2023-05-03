#include <vector>

#include <cppiter/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using cppiter::iter;

class UniqueRangeForRandomAccessTest : public Test {
public:
  std::vector<int> uniqueVec{ 1, 2, 3, 4, 5 };
  std::vector<int> v1{ 1, 1, 1, 1, 2, 3, 3, 4, 5, 5, 5 };
  std::vector<int> v2{ 1, 1, 1, 1 };
};

TEST_F(UniqueRangeForRandomAccessTest, UniqueRemovesDuplicates) {
  ASSERT_THAT(iter(v1).unique(), ElementsAreArray(uniqueVec));
}

TEST_F(UniqueRangeForRandomAccessTest, OutputOfUniqueVectorIsSameAsInput) {
  ASSERT_THAT(iter(uniqueVec).unique(), ElementsAreArray(uniqueVec));
}

TEST_F(UniqueRangeForRandomAccessTest, OutputIsSingleValueFromUniformValuedArray) {
  ASSERT_THAT(iter(v2).unique(), ElementsAre(1));
}

TEST_F(UniqueRangeForRandomAccessTest, EmptyTest) {
  ASSERT_THAT(iter(std::vector<int>{}).unique(), IsEmpty());
}
