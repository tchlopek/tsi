#pragma once

#include "range/generate_range.hpp"
#include "range/range_factory.hpp"

namespace tsi {

template<typename val_t>
auto gen(const val_t& v) {
  return rng::range_factory{ rng::generate_range{ v } };
}

}    // namespace tsi
