#pragma once

#include <go_cpp/typing/casters/decl.hpp>

namespace go_cpp::typing {

template <cast_type min_level_cast, typename To>
To autocast(auto&& from) {
    // check and log
    constexpr auto cur_level = caster_type<decltype(from), To>;
    auto checker = []<auto cur_level_cast>
        requires(cur_level_cast >= min_level_cast)
    {};
    checker.template operator()<cur_level>();
    return caster<decltype(from), To>::cast(std::forward<decltype(from)>(from));
}

#define def_autocast(X)                                     \
    template <typename To>                                  \
    To X##_autocast(auto&& from) {                          \
        constexpr auto cur_level = caster_type<decltype(from), To>; \
        auto checker = []<auto cur_level_cast> \
            requires(cur_level_cast >= cast_type::X) \
        {}; \
        checker.template operator()<cur_level>(); \
        return caster<decltype(from), To>::cast(            \
            std::forward<decltype(from)>(from));            \
    }

def_autocast(expanding);
def_autocast(narrowing);
def_autocast(explicit_simular);
def_autocast(implicit_simular);
def_autocast(equal);

#undef def_autocast

}  // namespace go_cpp::typing
