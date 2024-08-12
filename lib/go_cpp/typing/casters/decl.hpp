#pragma once

#include <go_cpp/typing/cast_type.hpp>
#include <utility>

namespace go_cpp::typing {
template <typename From, typename To>
struct caster {
    static constexpr auto type = cast_type::none;
};

template <typename From, typename To>
constexpr auto caster_type = caster<From, To>::type;

}  // namespace go_cpp::typing
