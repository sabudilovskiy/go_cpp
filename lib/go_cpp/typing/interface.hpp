#pragma once
#include <go_cpp/typing/autocast.hpp>
#include <go_cpp/typing/cast_type.hpp>

namespace go_cpp::typing {
template <typename To, cast_type min_level>
struct interface {
    template <typename From>
    interface(From&& from)
        : value(autocast<min_level, To>(std::forward<From>(from))) {}

    To* operator->() { return &value; }

    const To* operator->() const { return &value; }

    To value;
};

template <typename To>
using expanding_interface = interface<To, cast_type::expanding>;

template <typename To>
using narrowing_interface = interface<To, cast_type::narrowing>;

template <typename To>
using explicit_simular_interface = interface<To, cast_type::explicit_simular>;

template <typename To>
using implicit_simular_interface = interface<To, cast_type::explicit_simular>;

template <typename To>
using equal_interface = interface<To, cast_type::equal>;

};  // namespace go_cpp::typing
