#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <forward_list>
#include <list>
#include <vector>

#include <iter.hpp>

#include "matcher.hpp"

using namespace testing;
using cppiter::iter;

class StrideRangeForForwardIterator : public Test {
public:
    std::forward_list<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(StrideRangeForForwardIterator, ForwardIteratorTestFor2) {
    ASSERT_THAT(iter(v).stride(2), ElementsAre(1, 3, 5));
}

TEST_F(StrideRangeForForwardIterator, ForwardIteratorTestFor3) {
    ASSERT_THAT(iter(v).stride(3), ElementsAre(1, 4));
}


class StrideRangeForBidirectionalIterator : public Test {
public:
    std::list<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(StrideRangeForBidirectionalIterator, BidirectionalIteratorTestFor2) {
    ASSERT_THAT(iter(v).stride(2), ElementsAre(1, 3, 5));
}

TEST_F(StrideRangeForBidirectionalIterator, BidirectionalIteratorTestFor3) {
    ASSERT_THAT(iter(v).stride(3), ElementsAre(1, 4));
}


class StrideRangeForRandomAccess : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(StrideRangeForRandomAccess, RandomAccessIteratorTestFor2) {
    ASSERT_THAT(iter(v).stride(2), ElementsAre(1, 3, 5));
}

TEST_F(StrideRangeForRandomAccess, RandomAccessIteratorTestFor3) {
    ASSERT_THAT(iter(v).stride(3), ElementsAre(1, 4));
}

