#pragma once

#include "range/range_factory.hpp"

namespace tsi {

template<typename range_t>
auto iter(range_t&& range) {
  return rng::range_factory{ std::move(range) };
}

template<typename range_t>
auto iter(const range_t& range) {
  return rng::range_factory{ range };
}

}    // namespace tsi
