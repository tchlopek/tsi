#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct enumerate_iterator_traits {
    using iterator_category = std::conditional_t<
        std::is_same_v<category_t<Base>, std::bidirectional_iterator_tag>,
        std::forward_iterator_tag,
        category_t<Base>>;
    using difference_type = difference_t<Base>;
    using value_type = std::pair<difference_type, value_t<Base>>;
    using reference = std::pair<difference_type, reference_t<Base>>;
    using pointer = std::pair<difference_type, pointer_t<Base>>;
};

}

template<typename BaseIter>
class enumerate_iterator : public iterator_facade<
    enumerate_iterator<BaseIter>,
    detail::enumerate_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        enumerate_iterator<BaseIter>,
        detail::enumerate_iterator_traits<BaseIter>>;
    using Difference = typename BaseType::difference_type;

    friend class derived_access;

public:
    enumerate_iterator(BaseIter iter, Difference index) : iter{ iter }, index{ index }
    {}

private:
    bool equal(const enumerate_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
        ++index;
    }

    void decrement() {
        --iter;
        --index;
    }

    typename BaseType::reference dereference() const {
        return { index, std::ref(*iter) };
    }

    void advance(Difference n) {
        iter += n;
        index += n;
    }

    Difference distance_to(const enumerate_iterator& other) const {
        return iter - other.iter;
    }

    BaseIter iter;
    Difference index;
};

}
