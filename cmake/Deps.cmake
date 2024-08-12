include(cmake/CPM/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#10.2.0")
CPMAddPackage(
    NAME PFR
    GIT_REPOSITORY https://github.com/apolukhin/pfr_non_boost.git
    GIT_TAG 70858d68ca4d84b490141992a8f48a3fcc300fae
)

CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.12.1
    VERSION 1.12.1
    OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

CPMAddPackage(
    NAME magic_enum
    GITHUB_REPOSITORY Neargye/magic_enum
    GIT_TAG v0.9.5
)
