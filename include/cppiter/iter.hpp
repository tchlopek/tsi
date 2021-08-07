#pragma once

#include "range/range_factory.hpp"
#include "range/generate_range.hpp"

namespace cppiter {

template<typename R>
auto iter(R& r) {
    return range::range_factory<R>{ r };
}

template<typename R>
auto iter(const R& r) {
    return range::range_factory<const R>{ r };
}

template<typename T>
auto gen(const T& v) {
    return range::range_factory{ range::generate_range<T>{ v } };
}

}
