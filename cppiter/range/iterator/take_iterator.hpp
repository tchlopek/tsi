#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct take_iterator_traits {
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
class take_iterator :
    public iterator_facade<take_iterator<BaseIter>, detail::take_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        take_iterator<BaseIter>,
        detail::take_iterator_traits<BaseIter>>;

    friend class derived_access;

public:
    take_iterator(BaseIter iter, BaseIter end, std::size_t n) :
        iter{ iter }, end{ end }, n{ n }
    {
        align_iter();
    }

private:
    bool equal(const take_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        --n;
        ++iter;
        align_iter();
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    void align_iter() {
        if (n == 0) {
            iter = end;
        }
    }

    BaseIter iter;
    BaseIter end;
    std::size_t n;
};

}
