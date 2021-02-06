#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct unique_iterator_traits {
    using iterator_category = min_iterator_category_t<
        iterator_category_t<Base>,
        std::forward_iterator_tag>;
    using reference = reference_t<Base>;
    using difference_type = difference_t<Base>;
    using value_type = value_t<Base>;
    using pointer = pointer_t<Base>;
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
