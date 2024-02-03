#pragma once

#include <iterator>

namespace cppiter::rng::iter::util {

using fi = std::forward_iterator_tag;
using bi = std::bidirectional_iterator_tag;
using ri = std::random_access_iterator_tag;

}    // namespace cppiter::rng::iter::util