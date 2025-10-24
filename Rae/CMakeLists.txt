add_library(Rae)
add_library(Rae::Rae ALIAS Rae)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Rae/Config/Version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/Rae/Config/Version.hpp"
    @ONLY
)

target_sources(Rae
    PRIVATE
        Rae/Rae.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS 
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}/include
        FILES 
            Rae/Rae.hpp
            ${CMAKE_CURRENT_BINARY_DIR}/include/Rae/Config/Version.hpp
)

target_include_directories(Rae
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Rae PRIVATE Rae::warnings)

set_target_properties(Rae PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
