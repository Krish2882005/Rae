cmake_minimum_required(VERSION 3.28)

project(Rae
    VERSION 0.1.0
    DESCRIPTION "A Modern C++23 Application Framework"
    HOMEPAGE_URL "https://github.com/krish2882005/Rae"
    LANGUAGES CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Create a build directory.")
endif()

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

add_subdirectory(Rae)
