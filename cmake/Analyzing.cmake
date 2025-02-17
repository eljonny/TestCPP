if (TESTCPP_ANALYSIS_ENABLED)
    find_program (
        CLANG_TIDY_COMMAND
        NAMES
            clang-tidy
        NO_CACHE
    )

    if (NOT CLANG_TIDY_COMMAND)
        message (WARNING "clang-tidy is not found!")
        set (CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)

    else()
        set (
            CLANG_TIDY_COMMAND
"${CLANG_TIDY_COMMAND};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy;-p=${CMAKE_BINARY_DIR}"
            CACHE STRING "Clang Tidy command"
            FORCE
        )

        set_target_properties (
            ${PROJECT_NAME}
            PROPERTIES
                CXX_CLANG_TIDY
                "${CLANG_TIDY_COMMAND}"
        )

        message (STATUS "${PROJECT_NAME} clang-tidy enabled!")
    endif ()
endif ()
