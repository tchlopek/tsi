#include <vector>

#include <tsi/zip.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::zip;

template<typename... ts>
auto Tuple(const ts&... val) {
  return Eq(std::tuple{ val... });
}

class ZippedRangeTest : public Test {
public:
  std::vector<int> v1{ 1, 2, 3, 4 };
  std::vector<int> v2{ 10, 11, 12, 13 };
};

TEST_F(ZippedRangeTest, ShouldIterateOverElements) {
  ASSERT_THAT(
    zip(v1, v2),
    ElementsAre(Tuple(1, 10), Tuple(2, 11), Tuple(3, 12), Tuple(4, 13))
  );
}

TEST_F(ZippedRangeTest, ShouldNotExceedMinimalRange) {
  v1.insert(v1.end(), v2.begin(), v2.end());
  auto zipped = zip(v1, v2);
  EXPECT_EQ(zipped.size(), 4);
  ASSERT_THAT(
    zipped,
    ElementsAre(Tuple(1, 10), Tuple(2, 11), Tuple(3, 12), Tuple(4, 13))
  );
}
