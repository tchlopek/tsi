#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Iter>
struct unique_iterator_traits : iterator_traits_facade<
    Iter,
    min_iterator_category_t<category_t<Iter>, std::forward_iterator_tag>>
{};

}

template<typename Iter>
class unique_iterator :
    public iterator_facade<unique_iterator<Iter>, detail::unique_iterator_traits<Iter>> {

    friend class iterator_accessor;

public:
    unique_iterator(Iter iter, Iter end) : iter{ iter }, end{ end }
    {}

private:
    bool equal(const unique_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        const auto& beginVal = dereference();
        while (++iter != end && dereference() == beginVal);
    }

    reference_t<Iter> dereference() const {
        return *iter;
    }

    Iter iter;
    Iter end;
};

}
