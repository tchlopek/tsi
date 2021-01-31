#pragma once

#include <type_traits>

namespace cppiter::range::detail {

template<typename Range>
struct range_traits {
    using iterator = typename Range::iterator;
};

template<typename Value, std::size_t Size>
struct range_traits<Value[Size]> {
    using iterator = typename std::decay<Value[Size]>::type;
};

}
