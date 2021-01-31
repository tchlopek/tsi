#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

namespace cppiter::range {

template<typename R>
class identity_range :
    public range_facade<detail::range_iterator_t<R>> {
    using BaseRange = range_facade<detail::range_iterator_t<R>>;

public:
    explicit identity_range(R& range) :
        BaseRange { { std::begin(range) }, { std::end(range) } }
    {}
};

template<typename R>
identity_range<R> identity(R& range) {
    return identity_range<R>{ range };
}

template<typename R>
identity_range<const R> identity(const R& range) {
    return identity_range<const R>{ range };
}

}
