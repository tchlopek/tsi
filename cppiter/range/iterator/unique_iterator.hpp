#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct unique_iterator_traits {
    using iterator_category = min_iterator_category_t<
        typename std::iterator_traits<Base>::iterator_category,
        std::forward_iterator_tag>;
    using reference = typename std::iterator_traits<Base>::reference;
    using difference_type = typename std::iterator_traits<Base>::difference_type;
    using value_type = typename std::iterator_traits<Base>::value_type;
    using pointer = typename std::iterator_traits<Base>::pointer;
};

}

template<typename BaseIter>
class unique_iterator :
    public iterator_facade<unique_iterator<BaseIter>, detail::unique_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        unique_iterator<BaseIter>,
        detail::unique_iterator_traits<BaseIter>>;

public:
    unique_iterator(BaseIter iter, BaseIter end) : iter{ iter }, end{ end }
    {}

    bool equal(const unique_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        const auto& beginVal = dereference();
        while (++iter != end && dereference() == beginVal);
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

private:
    BaseIter iter;
    BaseIter end;
};

}
