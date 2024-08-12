#pragma once

namespace go_cpp::typing {
enum struct cast_type {
    none,
    expanding,
    narrowing,
    explicit_simular,
    implicit_simular,
    equal
};
}
