#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/take_iterator.hpp"

namespace cppiter::range {

template<typename R>
class take_range : public range_facade<iter::take_iterator<range_iterator_t<R>>> {
    using RngIt = range_iterator_t<R>;
    using TakeIt = iter::take_iterator<RngIt>;
    using Diff = iter::difference_t<RngIt>;

public:
    take_range(RngIt begin, RngIt end, Diff n) :
        take_range{ begin, end, n, iter::category_t<RngIt>{} }
    {}

private:
    take_range(RngIt begin, RngIt end, Diff n, std::forward_iterator_tag) :
        range_facade<TakeIt>{ TakeIt{ begin, 0 }, TakeIt{ end, n } }
    {}

    take_range(RngIt begin, RngIt end, Diff n, std::bidirectional_iterator_tag) :
        range_facade<TakeIt>{ TakeIt{ begin, 0 }, TakeIt{ end, n } }
    {}

    take_range(RngIt begin, RngIt end, Diff n, std::random_access_iterator_tag) :
        range_facade<TakeIt>{ TakeIt{ begin }, TakeIt{ begin + std::min(end - begin, n) } }
    {}
};

}
