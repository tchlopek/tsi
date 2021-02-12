#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <forward_list>
#include <list>
#include <vector>

#include <iter.hpp>

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

TEST_F(StrideRangeForForwardIterator, ExceededStrideReturnsFirstElement) {
    ASSERT_THAT(iter(v).stride(10), ElementsAre(1));
}

TEST_F(StrideRangeForForwardIterator, EmptyTest) {
    ASSERT_THAT(iter(std::forward_list<int>{}).stride(3), IsEmpty());
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

TEST_F(StrideRangeForBidirectionalIterator, ExceededStrideReturnsFirstElement) {
    ASSERT_THAT(iter(v).stride(10), ElementsAre(1));
}

TEST_F(StrideRangeForBidirectionalIterator, EmptyTest) {
    ASSERT_THAT(iter(std::list<int>{}).stride(3), IsEmpty());
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

TEST_F(StrideRangeForRandomAccess, ExceededStrideReturnsFirstElement) {
    ASSERT_THAT(iter(v).stride(10), ElementsAre(1));
}

TEST_F(StrideRangeForRandomAccess, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).stride(3), IsEmpty());
}
