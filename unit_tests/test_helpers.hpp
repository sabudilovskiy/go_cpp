#include <gtest/gtest.h>

#define EXPECT_THROW_MSG(type, msg, ...)                 \
    {                                                    \
        bool catched = false;                            \
        try {                                            \
            __VA_ARGS__;                                 \
        } catch (const type& exc) {                      \
            std::string_view got_msg = exc.what();       \
            std::string_view expected_msg = msg;         \
            catched = true;                              \
            EXPECT_EQ(got_msg, expected_msg) << got_msg; \
        }                                                \
        EXPECT_TRUE(catched);                            \
    };
