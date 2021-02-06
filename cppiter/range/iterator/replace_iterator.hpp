#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct replace_iterator_traits {
    using iterator_category = typename std::iterator_traits<Base>::iterator_category;
    using reference = detail::add_ref_const_t<typename std::iterator_traits<Base>::reference>;
    using difference_type = typename std::iterator_traits<Base>::difference_type;
    using value_type = typename std::iterator_traits<Base>::value_type;
    using pointer = detail::add_ref_const_t<typename std::iterator_traits<Base>::pointer>;
};

}

template<typename BaseIter, typename Pred>
class replace_iterator :
    public iterator_facade<
        replace_iterator<BaseIter, Pred>,
        detail::replace_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        replace_iterator<BaseIter, Pred>,
        detail::replace_iterator_traits<BaseIter>>;

    using ValueType = typename BaseType::value_type;

public:
    replace_iterator(BaseIter iter, Pred pred, const ValueType& newVal) :
        iter{ iter }, newVal{ newVal }, pred{ pred }
    {}

    bool equal(const replace_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    typename BaseType::reference dereference() const {
        return pred(*iter) ? newVal : *iter;
    }

    void advance(typename BaseType::difference_type n) {
        iter += n;
    }

    typename BaseType::difference_type distance_to(const replace_iterator& other) const {
        return iter - other.iter;
    }

private:
    BaseIter iter;
    ValueType newVal;
    Pred pred;
};

}
