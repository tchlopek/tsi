#pragma once

#include <type_traits>

#include "range/bound_range.hpp"
#include "range/range_factory.hpp"

namespace cppiter {

template<typename first_t, typename last_t>
auto range(first_t&& f, last_t&& l) {
  using _first_t = std::remove_cv_t<std::remove_reference_t<first_t>>;
  using _last_t = std::remove_cv_t<std::remove_reference_t<last_t>>;
  using common_t = std::common_type_t<_first_t, _last_t>;
  return rng::range_factory{ rng::bound_range{
    common_t(std::forward<first_t>(f)),
    common_t(std::forward<last_t>(l)) } };
}

}    // namespace cppiter