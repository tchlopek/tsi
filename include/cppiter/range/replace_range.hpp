#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/replace_iterator.hpp"

namespace cppiter::range {

template<typename R, typename P>
class replace_range : public range_facade<iter::replace_iterator<range_iterator_t<R>, P>> {
    using RngIt = range_iterator_t<R>;
    using ReplaceIt = iter::replace_iterator<RngIt, P>;

public:
    replace_range(RngIt begin, RngIt end, P pred, const iter::value_t<RngIt>& newVal) :
        range_facade<ReplaceIt>{ ReplaceIt{ begin, pred, newVal }, ReplaceIt{ end, pred, newVal } }
    {}
};

}
