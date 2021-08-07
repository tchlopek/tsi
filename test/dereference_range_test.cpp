#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <iter.hpp>

using namespace testing;
using cppiter::iter;

class DereferenceRangeTest : public Test {
public:
    std::vector<std::shared_ptr<int>> v{
        std::make_unique<int>(1),
        std::make_unique<int>(2),
        std::make_unique<int>(3)
    };
};

TEST_F(DereferenceRangeTest, DerefProducesDereferencedValues) {
    EXPECT_THAT(iter(v).deref(), ElementsAre(1, 2, 3));
}

TEST_F(DereferenceRangeTest, IsAbleToMutateSourceRange) {
    int c = 10;
    for (auto& e : iter(v).deref()) {
        e = c++;
    }

    EXPECT_THAT(v, ElementsAre(Pointee(10), Pointee(11), Pointee(12)));
}
