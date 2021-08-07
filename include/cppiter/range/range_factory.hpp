#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

#include "dereference_range.hpp"
#include "enumerate_range.hpp"
#include "flatten_range.hpp"
#include "filter_range.hpp"
#include "map_range.hpp"
#include "replace_range.hpp"
#include "reverse_range.hpp"
#include "skip_range.hpp"
#include "stride_range.hpp"
#include "take_range.hpp"
#include "unique_range.hpp"

namespace cppiter::range {

template<typename R>
class range_factory :
    public range_facade<range_iterator_t<R>> {
    using BaseRange = range_facade<range_iterator_t<R>>;

public:
    using BaseRange::begin;
    using BaseRange::end;

    range_factory(R& range) :
        BaseRange{ std::begin(range), std::end(range) }
    {}

    range_factory(R&& range) :
        BaseRange{ std::begin(range), std::end(range) }
    {}

    auto deref() {
        return range_factory<dereference_range<R>>{ { begin(), end() } };
    }

    auto enumerate(typename R::difference_type index = {}) {
        return range_factory<enumerate_range<R>>{ { begin(), end(), index } };
    }

    template<typename P>
    auto filter(P pred) {
        return range_factory<filter_range<R, P>>{ { begin(), end(), pred } };
    }

    auto flatten() {
        return range_factory<flatten_range<R>>{ { begin(), end() } };
    }

    template<typename F>
    auto map(F func) {
        return range_factory<map_range<R, F>>{ { begin(), end(), func } };
    }

    template<typename P>
    auto replace(P pred, const typename R::value_type& newVal) {
        return range_factory<replace_range<R, P>>{ { begin(), end(), pred, newVal } };
    }

    auto replace(const typename R::value_type& oldVal, const typename R::value_type& newVal) {
        const auto pred = [oldVal](const auto& current){ return oldVal == current; };
        return range_factory<replace_range<R, decltype(pred)>>{
            { begin(), end(), pred, newVal }
        };
    }

    auto reverse() {
        return range_factory<reverse_range<R>>{ { begin(), end() } };
    }

    auto skip(typename R::difference_type n) {
        return range_factory<skip_range<R>>{ { begin(), end(), n } };
    }

    auto stride(typename R::difference_type n) {
        return range_factory<stride_range<R>>{ { begin(), end(), n } };
    }

    auto take(typename R::difference_type n) {
        return range_factory<take_range<R>>{ { begin(), end(), n } };
    }

    auto unique() {
        return range_factory<unique_range<R>>{ { begin(), end() } };
    }

    template<typename T>
    T collect() {
        return T{ begin(), end() };
    }

    template<template<typename...> class C>
    auto collect() {
        using VT = typename range_facade<range_iterator_t<R>>::value_type;
        return C<VT>{ begin(), end() };
    }
};

}
