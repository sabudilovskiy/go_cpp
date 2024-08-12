#pragma once

namespace go_cpp::utils {
template <typename... Ts>
struct matcher : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
matcher(Ts...) -> matcher<Ts...>;
}  // namespace go_cpp::utils
