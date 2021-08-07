#pragma once

#include "range_facade.hpp"

#include "iterator/filter_iterator.hpp"

namespace cppiter::range {

template<typename R, typename P>
class filter_range : public range_facade<iter::filter_iterator<range_iterator_t<R>, P>> {
    using RngIt = range_iterator_t<R>;
    using FilterIt = iter::filter_iterator<RngIt, P>;

public:
    filter_range(RngIt begin, RngIt end, P pred) :
        filter_range{ begin, end, pred, iter::category_t<RngIt>{} }
    {}

private:
    filter_range(RngIt begin, RngIt end, P pred, std::forward_iterator_tag) :
        range_facade<FilterIt>{ FilterIt{ begin, end, pred }, FilterIt{ end, end, pred } }
    {}

    template<typename Cat>
    filter_range(RngIt begin, RngIt end, P pred, Cat) :
        range_facade<FilterIt>{
            FilterIt{ begin, std::pair{ begin, end }, pred },
            FilterIt{ end, std::pair{ begin, end }, pred }
        }
    {}
};

}
