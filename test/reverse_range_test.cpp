#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <list>
#include <forward_list>

#include <reverse_range.hpp>

using namespace testing;

class ReverseRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(ReverseRangeForRandomAccessTest, ReversedRangeHasOppositeOrderOfElements) {
    ASSERT_THAT(reverse(v), ElementsAre(5, 4, 3, 2, 1));
}

TEST_F(ReverseRangeForRandomAccessTest, DoublyReversedRangeHasSameOrderOfElements) {
    ASSERT_THAT(reverse(reverse(v)), ElementsAreArray(v));
}
