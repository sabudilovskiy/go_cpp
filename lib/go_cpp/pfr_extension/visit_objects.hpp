#pragma once

#pragma once
#include <go_cpp/pfr_extension/sorted_names.hpp>
#include <go_cpp/utils/fallback_type.hpp>

namespace go_cpp::pfr_extension {
namespace details {
template <std::size_t I, typename T>
decltype(auto) get_if_exist(T& t) {
    if constexpr (pfr::tuple_size_v<T> <= I) {
        return utils::fallback_type{};
    } else {
        return pfr::get<I>(t);
    }
}

template <utils::ce::string name>
void visit_one_field_with_name(auto& functor, auto&... t) {
    auto helper = []<typename U>(U& u) -> decltype(auto) {
        return get_if_exist<get_index<U, name>()>(u);
    };
    functor.template operator()<name>(helper(t)...);
}

template <std::size_t... I, typename... T>
void visit_objects_helper_with_name(std::index_sequence<I...>, auto& functor,
                                    T&... t) {
    constexpr auto set_of_names = get_set_of_names<std::remove_cvref_t<T>...>();
    auto visit_one_name = [&]<utils::ce::string name>() {
        visit_one_field_with_name<name>(functor, t...);
    };
    (visit_one_name.template operator()<set_of_names[I]>(), ...);
}

template <utils::ce::string name>
void visit_one_field(auto& functor, auto&... t) {
    auto helper = []<typename U>(U& u) -> decltype(auto) {
        return get_if_exist<get_index<U, name>()>(u);
    };
    functor(helper(t)...);
}

template <std::size_t... I, typename... T>
void visit_objects_helper(std::index_sequence<I...>, auto& functor, T&... t) {
    constexpr auto set_of_names = get_set_of_names<std::remove_cvref_t<T>...>();
    auto visit_one_name = [&]<utils::ce::string name>() {
        visit_one_field<name>(functor, t...);
    };
    (visit_one_name.template operator()<set_of_names[I]>(), ...);
}
}  // namespace details

template <typename... T>
void visit_objects_with_name(auto&& functor, T&&... t) {
    constexpr auto N = get_size_set_of_names<std::remove_cvref_t<T>...>();
    details::visit_objects_helper_with_name(std::make_index_sequence<N>{},
                                            functor, t...);
}

template <typename... T>
void visit_objects(auto&& functor, T&&... t) {
    constexpr auto N = get_size_set_of_names<std::remove_cvref_t<T>...>();
    details::visit_objects_helper(std::make_index_sequence<N>{}, functor, t...);
}

}  // namespace go_cpp::pfr_extension
