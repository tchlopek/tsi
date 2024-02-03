#pragma once

#include <tuple>

#include "iterator/zipped_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename... range_ts>
class zipped_range
  : public util::range_facade<zipped_range<range_ts...>>
  , public util::range_traits<
      iter::zipped_iterator<util::iterator_t<range_ts>...>,
      iter::zipped_iterator<util::const_iterator_t<range_ts>...>> {
  friend class util::range_accessor;

public:
  explicit zipped_range(range_ts&&... ranges)
    : m_ranges{ std::move(ranges)... } {
  }

private:
  auto make_begin() {
    return std::apply(
      [](auto&... rs) {
        return typename zipped_range::iterator{ rs.begin()... };
      },
      m_ranges
    );
  }

  auto make_end() {
    return std::apply(
      [](auto&... rs) { return typename zipped_range::iterator{ rs.end()... }; },
      m_ranges
    );
  }

  auto make_const_begin() const {
    return std::apply(
      [](auto&... rs) {
        return typename zipped_range::const_iterator{ rs.cbegin()... };
      },
      m_ranges
    );
  }

  auto make_const_end() const {
    return std::apply(
      [](auto&... rs) {
        return typename zipped_range::const_iterator{ rs.cend()... };
      },
      m_ranges
    );
  }

  std::tuple<range_ts...> m_ranges;
};

}    // namespace cppiter::rng
