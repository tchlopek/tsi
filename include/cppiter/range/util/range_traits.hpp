#pragma once

namespace cppiter::rng::util {

template<typename iter_t, typename const_iter_t>
struct range_traits {
  using iterator = iter_t;
  using const_iterator = const_iter_t;
  using reference = typename iter_t::reference;
  using const_reference = typename const_iter_t::reference;
  using value_type = typename iter_t::value_type;
  using difference_type = typename iter_t::difference_type;
};

}    // namespace cppiter::rng::util
