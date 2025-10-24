include_guard()

add_library(project_warnings INTERFACE)
add_library(Rae::warnings ALIAS project_warnings)

if(MSVC)
    target_compile_options(project_warnings INTERFACE
        /W4
        /permissive-
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(project_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(project_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wlogical-op
    )
endif()

message(STATUS "Compiler warnings configured for ${CMAKE_CXX_COMPILER_ID}")
