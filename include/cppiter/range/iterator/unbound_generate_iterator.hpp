#pragma once

#include "util/iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename T>
struct unbound_generate_iterator_traits : util::iterator_traits_facade<
    T,
    std::bidirectional_iterator_tag,
    T,
    T,
    std::add_pointer_t<T>,
    std::ptrdiff_t>
{};

}

template<typename T>
class unbound_generate_iterator :
    public util::iterator_facade<
        unbound_generate_iterator<T>,
        detail::unbound_generate_iterator_traits<T>> {

    friend class util::iterator_accessor;

public:
    explicit unbound_generate_iterator(T v) : v{ std::move(v) }
    {}

private:
    bool equal(const unbound_generate_iterator&) const {
        return false;
    }

    void increment() {
        ++v;
    }

    void decrement() {
        --v;
    }

    T dereference() const {
        return v;
    }

    mutable T v;
};

}
