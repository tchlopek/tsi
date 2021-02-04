#pragma once

#include "range_wrapper.hpp"

#include "range/identity_range.hpp"

namespace cppiter {

template<typename R>
range_wrapper<range::identity_range<R>> iter(R& r) {
    return range_wrapper{ range::identity(r) };
}

template<typename R>
range_wrapper<range::identity_range<const R>> iter(const R& r) {
    return range_wrapper{ range::identity(r) };
}

}
