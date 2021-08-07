#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/stride_iterator.hpp"

namespace cppiter::range {

template<typename R>
class stride_range : public range_facade<iter::stride_iterator<range_iterator_t<R>>> {
    using RngIt = range_iterator_t<R>;
    using StrideIt = iter::stride_iterator<RngIt>;
    using Diff = iter::difference_t<RngIt>;

public:
    stride_range(RngIt begin, RngIt end, Diff n) :
        stride_range{ begin, end, n, iter::category_t<RngIt>{} }
    {}

private:
    stride_range(RngIt begin, RngIt end, Diff n, std::forward_iterator_tag) :
        range_facade<StrideIt>{ StrideIt{ begin, end, n }, StrideIt{ end, end, n } }
    {}

    stride_range(RngIt begin, RngIt end, Diff n, std::bidirectional_iterator_tag) :
        range_facade<StrideIt>{
            StrideIt{ begin, 0, n },
            StrideIt{ end, std::distance(begin, end), n }
        }
    {}

    stride_range(RngIt begin, RngIt end, Diff n, std::random_access_iterator_tag) :
        range_facade<StrideIt>{
            StrideIt{ begin, begin, n },
            StrideIt{ begin, end, n }
        }
    {}
};

}
