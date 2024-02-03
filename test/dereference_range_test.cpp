#include <vector>

#include <tsi/iter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using tsi::iter;

class DereferenceRangeTest : public Test {
public:
  std::vector<std::shared_ptr<int>> v{ std::make_unique<int>(1),
                                       std::make_unique<int>(2),
                                       std::make_unique<int>(3) };
};

TEST_F(DereferenceRangeTest, DerefProducesDereferencedValues) {
  EXPECT_THAT(iter(v).deref(), ElementsAre(1, 2, 3));
}

using deref_t = tsi::rng::dereference_range<std::vector<const int*>>;

static_assert(std::is_same_v<deref_t::value_type, int>);
static_assert(std::is_same_v<deref_t::reference, const int&>);
static_assert(std::is_same_v<deref_t::iterator::pointer, const int*>);
