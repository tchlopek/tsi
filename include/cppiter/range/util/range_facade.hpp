#pragma once

namespace cppiter::rng::util {

class range_accessor {
public:
  template<typename range_t>
  static auto make_begin(range_t& range) {
    return range.make_begin();
  }

  template<typename range_t>
  static auto make_end(range_t& range) {
    return range.make_end();
  }

  template<typename range_t>
  static auto make_const_begin(range_t& range) {
    return range.make_const_begin();
  }

  template<typename range_t>
  static auto make_const_end(range_t& range) {
    return range.make_const_end();
  }
};

template<typename range_t>
class range_facade {
public:
  auto begin() {
    return range_accessor::make_begin(derived());
  }

  auto end() {
    return range_accessor::make_end(derived());
  }

  auto begin() const {
    return range_accessor::make_const_begin(derived());
  }

  auto end() const {
    return range_accessor::make_const_end(derived());
  }

  auto cbegin() const {
    return range_accessor::make_const_begin(derived());
  }

  auto cend() const {
    return range_accessor::make_const_end(derived());
  }

  bool empty() const {
    return begin() == end();
  }

  std::size_t size() const {
    return static_cast<std::size_t>(std::distance(begin(), end()));
  }

private:
  range_t& derived() {
    return static_cast<range_t&>(*this);
  }

  const range_t& derived() const {
    return static_cast<const range_t&>(*this);
  }
};
}    // namespace cppiter::rng::util
