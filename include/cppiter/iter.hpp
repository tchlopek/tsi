#pragma once

#include "cppiter/range/iterator/bound_generate_iterator.hpp"
#include "range/range_factory.hpp"
#include "range/generate_range.hpp"

namespace cppiter {

template<typename R>
auto iter(R& r) {
    return rng::range_factory<R>{ r };
}

template<typename R>
auto iter(const R& r) {
    return rng::range_factory<const R>{ r };
}

template<typename T>
auto gen(const T& v) {
    return rng::range_factory{ rng::generate_range<T>{ v } };
}

template<typename T>
auto range(const T& b, const T& e) {
    return rng::range_factory{
        rng::util::range_facade{
            rng::iter::bound_generate_iterator{ b },
            rng::iter::bound_generate_iterator{ e }
        }
    };
}

}
