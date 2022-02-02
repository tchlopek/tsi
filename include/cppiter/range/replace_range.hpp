#pragma once

#include "iterator/replace_iterator.hpp"

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::range {

template<typename R, typename P>
class replace_range : public util::range_facade<iter::replace_iterator<util::range_iterator_t<R>, P>> {
    using RngIt = util::range_iterator_t<R>;
    using ReplaceIt = iter::replace_iterator<RngIt, P>;

public:
    replace_range(RngIt begin, RngIt end, P pred, const iter::util::value_t<RngIt>& newVal) :
        util::range_facade<ReplaceIt>{ ReplaceIt{ begin, pred, newVal }, ReplaceIt{ end, pred, newVal } }
    {}
};

}
