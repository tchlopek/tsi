#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <forward_list>
#include <list>
#include <vector>

#include <iter.hpp>

using namespace testing;
using cppiter::iter;

class SkipRangeForForwardIterator : public Test {
public:
    std::forward_list<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(SkipRangeForForwardIterator, SkipReturnsTwoLastElements) {
    ASSERT_THAT(iter(v).skip(3), ElementsAre(4, 5));
}

TEST_F(SkipRangeForForwardIterator, ExceededSkipReturnsEmptyRange) {
    ASSERT_THAT(iter(v).skip(6), IsEmpty());
}

TEST_F(SkipRangeForForwardIterator, SkipZeroReturnsSourceRange) {
    ASSERT_THAT(iter(v).skip(0), ElementsAreArray(v));
}

TEST_F(SkipRangeForForwardIterator, EmptyTest) {
    ASSERT_THAT(iter(std::forward_list<int>{}).skip(10), IsEmpty());
}

class SkipRangeForBidirectionalIterator : public Test {
public:
    std::list<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(SkipRangeForBidirectionalIterator, SkipReturnsTwoLastElements) {
    ASSERT_THAT(iter(v).skip(3), ElementsAre(4, 5));
}

TEST_F(SkipRangeForBidirectionalIterator, ExceededSkipReturnsEmptyRange) {
    ASSERT_THAT(iter(v).skip(5), IsEmpty());
}

TEST_F(SkipRangeForBidirectionalIterator, SkipZeroReturnsSourceRange) {
    ASSERT_THAT(iter(v).skip(0), ElementsAreArray(v));
}

TEST_F(SkipRangeForBidirectionalIterator, EmptyTest) {
    ASSERT_THAT(iter(std::list<int>{}).skip(10), IsEmpty());
}

class SkipRangeForRandomAccessIterator : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(SkipRangeForRandomAccessIterator, SkipReturnsFourLastElements) {
    ASSERT_THAT(iter(v).skip(1), ElementsAre(2, 3, 4, 5));
}

TEST_F(SkipRangeForRandomAccessIterator, ExceededSkipReturnsEmptyRange) {
    ASSERT_THAT(iter(v).skip(6), IsEmpty());
}

TEST_F(SkipRangeForRandomAccessIterator, SkipZeroReturnsSourceRange) {
    ASSERT_THAT(iter(v).skip(0), ElementsAreArray(v));
}

TEST_F(SkipRangeForRandomAccessIterator, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).skip(10), IsEmpty());
}
