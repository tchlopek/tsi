#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/replace_iterator.hpp"

namespace cppiter::range {

template<typename R, typename P>
class replace_range :
    public range_facade<iter::replace_iterator<detail::range_iterator_t<R>, P>> {
    using BaseRange = range_facade<iter::replace_iterator<detail::range_iterator_t<R>, P>>;

public:
    replace_range(
        detail::range_iterator_t<R> begin,
        detail::range_iterator_t<R> end,
        P pred,
        const typename BaseRange::value_type& newVal) :
            BaseRange{ { begin, pred, newVal }, { end, pred, newVal } }
    {}
};

}
