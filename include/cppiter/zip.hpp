#pragma once

#include "range/range_factory.hpp"
#include "range/zipped_range.hpp"

namespace cppiter {

template<typename... range_ts>
auto zip(range_ts&&... rs) {
  return rng::range_factory{ rng::zipped_range{ std::move(rs)... } };
}

}    // namespace cppiter
