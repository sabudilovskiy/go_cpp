#pragma once

#include <go_cpp/utils/constexpr_string.hpp>
#include <string_view>

namespace go_cpp::pfr_extension {
template <std::size_t Index, utils::ce::string Name>
struct field_info {
    static constexpr auto index = Index;
    static constexpr auto name = Name;
};
}  // namespace go_cpp::pfr_extension
