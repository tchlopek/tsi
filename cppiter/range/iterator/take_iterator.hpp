#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct take_iterator_traits {
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
class take_iterator :
    public iterator_facade<take_iterator<BaseIter>, detail::take_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        take_iterator<BaseIter>,
        detail::take_iterator_traits<BaseIter>>;

public:
    take_iterator(BaseIter iter, BaseIter end, std::size_t n) :
        iter{ iter }, end{ end }, n{ n }
    {
        align_iter();
    }

    bool equal(const take_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        --n;
        ++iter;
        align_iter();
    }

    typename BaseType::reference dereference() {
        return *iter;
    }

private:
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
