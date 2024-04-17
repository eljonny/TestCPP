set (MSVC_RELEASE_BUILD_OPTS "/Wall /WX /O2 /wd4710")
set (MSVC_DEBUG_BUILD_OPTS "/Wall /WX /Od /wd4710")
set (GCC_CLANG_RELEASE_BUILD_OPTS "-O3 -Wall -Wextra -Wpedantic")
set (GCC_CLANG_DEBUG_BUILD_OPTS "-g -Og -Wall -Wextra -Wpedantic")
set (COVERAGE_BUILD_OPTS "-g -Og -Wall -Wextra -Wpedantic\
-fprofile-arcs -ftest-coverage")

if (${CMAKE_BUILD_TYPE} EQUAL "Release")
    message (STATUS "Release build compilation options enabled")

    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            ${MSVC_RELEASE_BUILD_OPTS}
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                ${MSVC_RELEASE_BUILD_OPTS}
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                ${MSVC_RELEASE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${MSVC_RELEASE_BUILD_OPTS}
            )
        endif ()

    else ()
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            ${GCC_CLANG_RELEASE_BUILD_OPTS}
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                ${GCC_CLANG_RELEASE_BUILD_OPTS}
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                ${GCC_CLANG_RELEASE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${GCC_CLANG_RELEASE_BUILD_OPTS}
            )
        endif ()
    endif ()

else ()
    message (STATUS "Debug build compilation options enabled")

    target_compile_definitions (
        ${PROJECT_NAME}
        PUBLIC
        DEBUG_LOG
    )

    if (${TESTCPP_DEMO_ENABLED})
        target_compile_definitions (
            ${PROJECT_NAME}_run
            PUBLIC
            DEBUG_LOG
        )
    endif ()

    if (BUILD_TESTING)
        target_compile_definitions (
            ${PROJECT_NAME}_TestCase_test
            PUBLIC
            DEBUG_LOG
        )
        target_compile_definitions (
            ${PROJECT_NAME}_TestSuite_test
            PUBLIC
            DEBUG_LOG
        )
    endif ()

    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            ${MSVC_DEBUG_BUILD_OPTS}
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                ${MSVC_DEBUG_BUILD_OPTS}
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                ${MSVC_DEBUG_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${MSVC_DEBUG_BUILD_OPTS}
            )
        endif ()

    else ()
        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                ${GCC_CLANG_DEBUG_BUILD_OPTS}
            )
        endif ()

        if (BUILD_TESTING AND ${TESTCPP_COVERAGE_ENABLED})
            message (STATUS "Coverage compilation options enabled")

            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                ${COVERAGE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                ${COVERAGE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${COVERAGE_BUILD_OPTS}
            )

        else ()
            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                ${GCC_CLANG_DEBUG_BUILD_OPTS}
            )
        endif ()
    endif ()
endif ()

if (${TESTCPP_STACKTRACE_ENABLED})
    target_compile_definitions (
        ${PROJECT_NAME}
        PUBLIC
        TESTCPP_STACKTRACE_ENABLED
    )
endif ()
