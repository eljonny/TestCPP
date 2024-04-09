if (${CMAKE_BUILD_TYPE} EQUAL "Release")
    message (STATUS "Release build compilation options enabled")

    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            /Wall /WX /O2
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                /Wall /WX /O2
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                /Wall /WX /O2
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                /Wall /WX /O2
            )
        endif ()

    else ()
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            -O3 -Wall -Wextra -Wpedantic
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )
        endif ()
    endif ()

else ()
    message (STATUS "Debug build compilation options enabled")

    target_compile_definitions (${PROJECT_NAME} PUBLIC DEBUG_LOG)

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
            /Wall /WX /Od
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                /Wall /WX /Od
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                /Wall /WX /Od
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                /Wall /WX /Od
            )
        endif ()

    else ()
        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC -g -Og -Wall -Wextra -Wpedantic
            )
        endif ()

        if (BUILD_TESTING AND ${TESTCPP_COVERAGE_ENABLED})
            message (STATUS "Coverage compilation options enabled")

            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )

            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )

        else ()
            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC -g -Og -Wall -Wextra -Wpedantic
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
