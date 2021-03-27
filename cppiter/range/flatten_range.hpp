#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/flatten_iterator.hpp"

namespace cppiter::range {

template<typename R>
class flatten_range : public range_facade<iter::flatten_iterator<range_iterator_t<R>>> {
    using Iterator = iter::flatten_iterator<range_iterator_t<R>>;

public:
    flatten_range(range_iterator_t<R> begin, range_iterator_t<R> end) :
        flatten_range{ begin, end, iter::category_t<Iterator>{} }
    {}

private:
    flatten_range(range_iterator_t<R> begin, range_iterator_t<R> end, std::forward_iterator_tag) :
        range_facade<Iterator>{ { begin, end, begin->begin() }, { end, end, {} } }
    {}

    template<typename Category>
    flatten_range(range_iterator_t<R> begin, range_iterator_t<R> end, Category) :
        range_facade<Iterator>{ { begin, end, begin, begin->begin() }, { begin, end, end, {} } }
    {}
};

}
