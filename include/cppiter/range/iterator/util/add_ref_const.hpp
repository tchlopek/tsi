#pragma once

namespace cppiter::range::iter::util {

template<typename T>
struct add_ref_const;

template<typename T>
struct add_ref_const<T&> {
    using type = const T&;
};

template<typename T>
struct add_ref_const<const T&> {
    using type = const T&;
};

template<typename T>
struct add_ref_const<T*> {
    using type = const T*;
};

template<typename T>
struct add_ref_const<const T*> {
    using type = const T*;
};

template<typename T>
using add_ref_const_t = typename add_ref_const<T>::type;

}