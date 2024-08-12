cmake_minimum_required(VERSION 3.20)

project(go-cpp)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
include(cmake/utils/CreatePart.cmake)
include(cmake/utils/CreateVariable.cmake)
include(cmake/utils/InitializeCppMacro.cmake)
include(cmake/Options.cmake)
include(cmake/Deps.cmake)

enable_testing()

include(Library.cmake)

if (${PROJECT_NAME}_BUILD_UNIT_TESTS)
    message(STATUS "GO_CPP BUILD UNIT TESTS : enabled")
    include(unit_tests/CMakeLists.txt)
else ()
    message(STATUS "GO_CPP BUILD UNIT TESTS : disabled")
endif ()

unset (library_module)


