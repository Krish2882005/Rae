include_guard()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY 
            "${CLANG_TIDY_EXE}"
            "--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy"
        )
        message(STATUS "clang-tidy: ENABLED")
    else()
        message(WARNING "clang-tidy: NOT FOUND")
    endif()
else()
    message(STATUS "clang-tidy: DISABLED")
endif()
