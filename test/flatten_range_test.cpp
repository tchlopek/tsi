#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <forward_list>
#include <list>

#include <iter.hpp>

using namespace testing;
using cppiter::iter;

class FlattenRangeForForwardIterator : public Test {
public:
    std::vector<std::forward_list<int>> v1{ {}, {}, { 1, 2, 3 }, {}, { 4, 5, 6 }, {} };
    std::vector<std::forward_list<int>> v2{ {}, {}, { 1, 2, 3 }, {}, { 4, 5, 6 } };
};

TEST_F(FlattenRangeForForwardIterator, test1) {
    ASSERT_THAT(iter(v1).flatten(), ElementsAre(1, 2, 3, 4, 5, 6));
}

TEST_F(FlattenRangeForForwardIterator, test2) {
    ASSERT_THAT(iter(v2).flatten(), ElementsAre(1, 2, 3, 4, 5, 6));
}

class FlattenRangeForBidirectionalIterator : public Test {
public:
    std::vector<std::list<int>> v1{ {}, {}, { 1, 2, 3 }, {}, { 4, 5, 6 }, {} };
    std::vector<std::list<int>> v2{ {}, {}, { 1, 2, 3 }, {}, { 4, 5, 6 } };
    std::vector<std::vector<std::list<int>>> v3{
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
        }
    };
};

TEST_F(FlattenRangeForBidirectionalIterator, test1) {
    ASSERT_THAT(iter(v1).flatten(), ElementsAre(1, 2, 3, 4, 5, 6));
}

TEST_F(FlattenRangeForBidirectionalIterator, test2) {
    ASSERT_THAT(iter(v2).flatten(), ElementsAre(1, 2, 3, 4, 5, 6));
}

TEST_F(FlattenRangeForBidirectionalIterator, test3) {
    ASSERT_THAT(iter(v3).flatten().flatten(), ElementsAre(1, 2, 3, 4, 5, 6));
}

