#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "filter_range.hpp"
#include "reverse_range.hpp"
#include "map_range.hpp"

namespace cppiter::range {

template<typename R>
class range_factory :
    public range_facade<detail::range_iterator_t<R>> {
    using BaseRange = range_facade<detail::range_iterator_t<R>>;

public:
    using BaseRange::begin;
    using BaseRange::end;

    range_factory(R& range) :
        BaseRange{ std::begin(range), std::end(range) }
    {}

    range_factory(const R& range) :
        BaseRange{ std::begin(range), std::end(range) }
    {}

    template<typename P>
    auto filter(P pred) {
        return range_factory<filter_range<R, P>>{ filter_range<R, P>{ begin(), end(), pred } };
    }

    auto reverse() {
        return range_factory<reverse_range<R>>{ reverse_range<R>{ begin(), end() } };
    }

    template<typename F>
    auto map(F func) {
        return range_factory<map_range<R, F>>{ map_range<R, F>{ begin(), end(), func } };
    }
};

}
