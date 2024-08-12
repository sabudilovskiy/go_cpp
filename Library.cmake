CreateTrivialPart(
        name "library"
        path "/lib"
)

target_compile_options(${library_module} ${${PROJECT_NAME}_COMPILE_OPTIONS_VISIBLE} "-Wno-missing-field-initializers")
target_link_libraries(${library_module} INTERFACE fmt)
target_link_libraries(${library_module} INTERFACE magic_enum)
target_link_libraries(${library_module} INTERFACE boost_pfr)

InitializeCppMacro(
        target ${library_module}
        name_macro GO_CPP_FIXED_STRING_SIZE
        variable FIXED_STRING_SIZE
)
