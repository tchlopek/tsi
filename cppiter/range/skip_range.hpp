#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

namespace cppiter::range {

template<typename R>
class skip_range :
    public range_facade<range_iterator_t<R>> {
    using Iterator = range_iterator_t<R>;

public:
    skip_range(Iterator begin, Iterator end, iter::difference_t<Iterator> n) :
        range_facade<Iterator>{
            { makeBeginIter<iter::category_t<Iterator>>(begin, end, n) },
            { end }
        }
    {}

private:
    template<typename Category>
    Iterator makeBeginIter(Iterator begin, Iterator end, iter::difference_t<Iterator> n) {
        if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
            return begin + std::min(end - begin, n);
        } else {
            for (; begin != end && n-- > 0; ++begin);
            return begin;
        }
    }
};

}
