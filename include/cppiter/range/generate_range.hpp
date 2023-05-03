#pragma once

#include "iterator/unbound_generate_iterator.hpp"
#include "util/range_facade.hpp"

namespace cppiter::rng {

template<typename T>
class generate_range
  : public util::range_facade<iter::unbound_generate_iterator<T>> {
  using I = iter::unbound_generate_iterator<T>;

public:
  generate_range(const T& v)
    : util::range_facade<I>{ I{ v }, I{ v } } {
  }

  std::size_t size() const = delete;
};

}    // namespace cppiter::rng
