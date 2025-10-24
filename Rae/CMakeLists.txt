add_library(Rae)
add_library(Rae::Rae ALIAS Rae)

target_sources(Rae
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES Rae/Rae.hpp
)

target_include_directories(Rae
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(Rae PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    
    LINKER_LANGUAGE CXX
)
