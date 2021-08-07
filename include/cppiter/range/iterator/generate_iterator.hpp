#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename T>
struct generate_iterator_traits : iterator_traits_facade<
    T,
    std::bidirectional_iterator_tag,
    T,
    T,
    std::add_pointer_t<T>,
    std::ptrdiff_t>
{};

}

template<typename T>
class generate_iterator :
    public iterator_facade<generate_iterator<T>, detail::generate_iterator_traits<T>> {

    friend class derived_access;

public:
    explicit generate_iterator(T v) : v{ std::move(v) }
    {}

private:
    bool equal(const generate_iterator& other) const {
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