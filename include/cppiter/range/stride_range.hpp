#pragma once

#include "iterator/stride_iterator.hpp"

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class stride_range : public util::range_facade<iter::stride_iterator<util::range_iterator_t<R>>> {
    using RngIt = util::range_iterator_t<R>;
    using StrideIt = iter::stride_iterator<RngIt>;
    using Diff = iter::util::difference_t<RngIt>;

public:
    stride_range(RngIt begin, RngIt end, Diff n) :
        stride_range{ begin, end, n, iter::util::category_t<RngIt>{} }
    {}

private:
    template<typename C>
    stride_range(RngIt begin, RngIt end, Diff n, C) :
        util::range_facade<StrideIt>{ StrideIt{ begin, end, n }, StrideIt{ end, end, n } }
    {}

    stride_range(RngIt begin, RngIt end, Diff n, std::random_access_iterator_tag) :
        util::range_facade<StrideIt>{
            StrideIt{ begin, begin, n },
            StrideIt{ begin, end, n }
        }
    {}
};

}
