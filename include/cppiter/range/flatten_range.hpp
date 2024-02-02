#pragma once

#include "iterator/flatten_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t>
class flatten_range
  : public util::range_facade<flatten_range<range_t>>
  , public util::range_traits<
      iter::flatten_iterator<util::iterator_t<range_t>, flatten_range<range_t>>,
      iter::flatten_iterator<
        util::const_iterator_t<range_t>,
        const flatten_range<range_t>>> {
  friend class util::range_accessor;

  template<typename, typename>
  friend class iter::flatten_iterator;

public:
  explicit flatten_range(range_t&& range)
    : m_range{ std::move(range) } {
  }

private:
  auto make_begin() {
    return typename flatten_range::iterator{ m_range.begin(),
                                             m_range.begin()->begin(),
                                             this };
  }

  auto make_end() {
    return typename flatten_range::iterator{ m_range.end(), {}, this };
  }

  auto make_const_begin() const {
    return typename flatten_range::const_iterator{ m_range.cbegin(),
                                                   m_range.cbegin()->cbegin(),
                                                   this };
  }

  auto make_const_end() const {
    return typename flatten_range::const_iterator{ m_range.cend(), {}, this };
  }

  range_t m_range;
};

}    // namespace cppiter::rng
