#pragma once

#include <type_traits>

#include "iterator/util/category_types.hpp"
#include "iterator/util/iterator_traits.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace tsi::rng {

template<typename range_t>
class skip_range
  : public util::range_facade<skip_range<range_t>>
  , public util::
      range_traits<util::iterator_t<range_t>, util::const_iterator_t<range_t>> {
  friend class util::range_accessor;

public:
  skip_range(range_t&& range, std::ptrdiff_t n)
    : m_range{ std::move(range) }
    , m_beg{ get_begin(m_range.begin(), m_range.end(), n) }
    , m_cbeg{ get_begin(m_range.cbegin(), m_range.cend(), n) } {
  }

private:
  template<typename iter_t>
  auto get_begin(iter_t&& begin, iter_t&& end, std::ptrdiff_t n) {
    if constexpr (std::is_same_v<iter::util::category_t<iter_t>, iter::util::ri>) {
      return begin + std::min(end - begin, n);
    } else {
      for (; begin != end && n-- > 0; ++begin)
        ;
      return begin;
    }
  }

  auto make_begin() {
    return m_beg;
  }

  auto make_end() {
    return typename skip_range::iterator{ m_range.end() };
  }

  auto make_const_begin() const {
    return m_cbeg;
  }

  auto make_const_end() const {
    return typename skip_range::const_iterator{ m_range.cend() };
  }

  range_t m_range;
  typename skip_range::iterator m_beg;
  typename skip_range::const_iterator m_cbeg;
};

}    // namespace tsi::rng
