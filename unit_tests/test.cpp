//
// Created by sabudilovskiy on 6/27/24.
//

#include <go_cpp/all.hpp>
#include <test_helpers.hpp>

enum struct Color1 { Red, Green, Blue };

enum struct Color2 { Blue, Green, Red };

enum struct Color3 { Blue, Green };

enum struct Color4 { Green, Red };

enum struct Color5 { Black, White };

static_assert(go_cpp::typing::caster_type<Color1, Color2> ==
              go_cpp::typing::cast_type::equal);
static_assert(go_cpp::typing::caster_type<Color1, Color3> ==
              go_cpp::typing::cast_type::narrowing);
static_assert(go_cpp::typing::caster_type<Color3, Color1> ==
              go_cpp::typing::cast_type::expanding);
static_assert(go_cpp::typing::caster_type<Color1, Color5> ==
              go_cpp::typing::cast_type::none);

TEST(EnumTests, Basic) {
    Color1 c1 = Color1::Red;
    auto test_interface = [&](go_cpp::typing::expanding_interface<Color2> c2) {
        EXPECT_EQ(c2.value, Color2::Red);
    };
    test_interface(c1);
}

TEST(EnumTests, Basic2) {
    Color1 c1 = Color1::Red;

    auto test_interface = [&](go_cpp::typing::expanding_interface<Color3>) {};
    EXPECT_THROW_MSG(go_cpp::utils::formatted_exception, "",
                     test_interface(c1));
}
