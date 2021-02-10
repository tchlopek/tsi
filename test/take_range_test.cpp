#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <forward_list>
#include <list>
#include <vector>

#include <iter.hpp>

#include "matcher.hpp"

using namespace testing;
using cppiter::iter;

class TakeRangeForForwardIterator : public Test {
public:
    std::forward_list<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(TakeRangeForForwardIterator, TakeHasOnlyThreeElements) {
    ASSERT_THAT(iter(v).take(3), ElementsAre(1, 2, 3));
}

TEST_F(TakeRangeForForwardIterator, ExceededTakeReturnSourceRange) {
    ASSERT_THAT(iter(v).take(10), ElementsAreArray(v));
}

TEST_F(TakeRangeForForwardIterator, TakeIsEmpty) {
    ASSERT_THAT(iter(v).take(0), utest::IsEmpty());
}

TEST_F(TakeRangeForForwardIterator, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).take(10), utest::IsEmpty());
}

class TakeRangeForBidirectionalIterator : public Test {
public:
    std::list<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(TakeRangeForBidirectionalIterator, TakeHasOnlyThreeElements) {
    ASSERT_THAT(iter(v).take(3), ElementsAre(1, 2, 3));
}

TEST_F(TakeRangeForBidirectionalIterator, ExceededTakeReturnSourceRange) {
    ASSERT_THAT(iter(v).take(10), ElementsAreArray(v));
}

TEST_F(TakeRangeForBidirectionalIterator, TakeIsEmpty) {
    ASSERT_THAT(iter(v).take(0), utest::IsEmpty());
}

TEST_F(TakeRangeForBidirectionalIterator, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).take(10), utest::IsEmpty());
}

class TakeRangeForRandomAccessIterator : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(TakeRangeForRandomAccessIterator, TakeHasOnlyThreeElements) {
    ASSERT_THAT(iter(v).take(3), ElementsAre(1, 2, 3));
}

TEST_F(TakeRangeForRandomAccessIterator, ExceededTakeReturnSourceRange) {
    ASSERT_THAT(iter(v).take(10), ElementsAreArray(v));
}

TEST_F(TakeRangeForRandomAccessIterator, TakeIsEmpty) {
    ASSERT_THAT(iter(v).take(0), utest::IsEmpty());
}

TEST_F(TakeRangeForRandomAccessIterator, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).take(10), utest::IsEmpty());
}
