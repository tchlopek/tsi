#pragma once

#include <type_traits>

namespace cppiter::range {

template<typename Range>
struct range_iterator {
    using type = typename Range::iterator;
};

template<typename Range>
struct range_iterator<const Range> {
    using type = typename Range::const_iterator;
};

template<typename Value, std::size_t Size>
struct range_iterator<Value[Size]> {
    using type = std::decay_t<Value[Size]>;
};

template<typename Range>
using range_iterator_t = typename range_iterator<Range>::type;

}
