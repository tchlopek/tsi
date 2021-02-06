#pragma once

#include "range/range_factory.hpp"

namespace cppiter {

template<typename R>
range::range_factory<R> iter(R& r) {
    return range::range_factory<R>{ r };
}

template<typename R>
range::range_factory<const R> iter(const R& r) {
    return range::range_factory<const R>{ r };
}

}
