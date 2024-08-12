#pragma once

#include <algorithm>
#include <go_cpp/typing/casters/decl.hpp>
#include <go_cpp/utils/formatted_exception.hpp>
#include <go_cpp/utils/name_type.hpp>
#include <magic_enum.hpp>

namespace go_cpp::typing {

namespace details {
template <typename From, typename To>
constexpr cast_type get_cast_level() {
    std::array from_names = magic_enum::enum_names<From>();
    std::array to_names = magic_enum::enum_names<To>();
    std::sort(from_names.begin(), from_names.end());
    std::sort(to_names.begin(), to_names.end());
    auto it = from_names.begin();
    auto it2 = to_names.begin();

    bool exist_intersection = false;
    bool add_elems_in_from = false;
    bool add_elems_in_to = false;
    while (it != from_names.end() || it2 != to_names.end()) {
        if (it == from_names.end()) {
            add_elems_in_to = true;
            ++it2;
            continue;
        }
        if (it2 == to_names.end()) {
            add_elems_in_from = true;
            ++it;
            continue;
        }
        if (*it == *it2) {
            exist_intersection = true;
            ++it;
            ++it2;
        } else if (*it < *it2) {
            add_elems_in_from = true;
            ++it;
        } else {
            add_elems_in_to = true;
            ++it2;
        }
    }
    if (!exist_intersection) {
        return cast_type::none;
    }
    if (add_elems_in_from) {
        return cast_type::narrowing;
    }
    if (add_elems_in_to) {
        return cast_type::expanding;
    }
    return cast_type::equal;
}

}  // namespace details

template <typename From, typename To>
requires std::is_enum_v<std::remove_cvref_t<From>> && std::is_enum_v<To>
struct caster<From, To> {
    /*
     * Возможно четыре случая:
     * 1) никакие имена из From не представлены в To. cast_type - none
     * 2) часть имён представлено в To, cast_type - narrowing
     * 3) все имена представлены в To, но там есть прочие имена. cast_type -
     * expanding 4) множества имен совпадают. cast_type - equal
     */
    static constexpr cast_type type =
        details::get_cast_level<std::remove_cvref_t<From>, To>();
    static To cast(From from) {
        auto name = magic_enum::enum_name(from);
        std::optional<To> value = magic_enum::enum_cast<To>(name);
        if (value) {
            return *value;
        }
        throw utils::formatted_exception("[{}] is not represented in [{}]", name,
                                         utils::get_type_name_info<To>().name);
    }
};
}  // namespace go_cpp::typing
