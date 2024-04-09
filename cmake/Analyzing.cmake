if (TESTCPP_ANALYSIS_ENABLED)
    find_program (CLANG_TIDY_COMMAND NAMES clang-tidy)

    if (NOT CLANG_TIDY_COMMAND)
        message (WARNING "clang-tidy is not found!")
        set (CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)

    else()
        set (
            CLANG_TIDY_COMMAND
"${CLANG_TIDY_COMMAND};--header-filter=.*;--format-style=file;\
-p=${CMAKE_BINARY_DIR}"
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
