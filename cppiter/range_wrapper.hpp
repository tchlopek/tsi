#pragma once

#include "range/range_facade.hpp"
#include "range/filter_range.hpp"
#include "range/reverse_range.hpp"
#include "range/map_range.hpp"

namespace cppiter {

template<typename R>
class range_wrapper :
    public range::range_types_facade<typename R::iterator> {
public:
    explicit range_wrapper(const R& range) : r{ range }
    {}

    typename R::iterator begin() const {
        return r.begin();
    }

    typename R::iterator end() const {
        return r.end();
    }

    template<typename P>
    range_wrapper<range::filter_range<R, P>> filter(P pred) {
        return range_wrapper<range::filter_range<R, P>>{ range::filter(r, pred) };
    }

    range_wrapper<range::reverse_range<R>> reverse() {
        return range_wrapper<range::reverse_range<R>>{ range::reverse(r) };
    }

    template<typename F>
    range_wrapper<range::map_range<R, F>> map(F func) {
        return range_wrapper<range::map_range<R, F>>{ range::map(r, func) };
    }

private:
    R r;
};

}
