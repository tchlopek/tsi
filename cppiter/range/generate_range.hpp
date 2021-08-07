#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/generate_iterator.hpp"

namespace cppiter::range {

template<typename T>
class generate_range : public range_facade<iter::generate_iterator<T>> {
    using I = iter::generate_iterator<T>;

public:
    generate_range(const T& v) : range_facade<I>{ I{ v }, I{ v } }
    {}

    std::size_t size() const = delete;
};

}
