if (${TESTCPP_DEMO_ENABLED})
    if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
        target_link_libraries (
            ${PROJECT_NAME}_run
            ${PROJECT_NAME}
            ole32
            dbgeng
        )

    elseif (${TESTCPP_STACKTRACE_ENABLED})
        target_link_libraries (
            ${PROJECT_NAME}_run
            ${PROJECT_NAME}
            dl
        )

    else ()
        target_link_libraries (
            ${PROJECT_NAME}_run
            ${PROJECT_NAME}
        )
    endif ()
endif ()

if (BUILD_TESTING)
    if (${TESTCPP_COVERAGE_ENABLED})
        message (STATUS "Linking in gcov")

        target_link_libraries (
            ${PROJECT_NAME}
            gcov
        )

        if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
            target_link_libraries (
                ${PROJECT_NAME}_TestCase_test
                ${PROJECT_NAME}
                gcov
                ole32
                dbgeng
            )
            target_link_libraries (
                ${PROJECT_NAME}_TestSuite_test
                ${PROJECT_NAME}
                gcov
                ole32
                dbgeng
            )

        elseif (${TESTCPP_STACKTRACE_ENABLED})
            target_link_libraries (
                ${PROJECT_NAME}_TestCase_test
                ${PROJECT_NAME}
                gcov
                dl
            )
            target_link_libraries (
                ${PROJECT_NAME}_TestSuite_test
                ${PROJECT_NAME}
                gcov
                dl
            )

        else ()
            target_link_libraries (
                ${PROJECT_NAME}_TestCase_test
                ${PROJECT_NAME}
                gcov
            )
            target_link_libraries (
                ${PROJECT_NAME}_TestSuite_test
                ${PROJECT_NAME}
                gcov
            )
        endif ()

    else ()
        if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
            target_link_libraries (
                ${PROJECT_NAME}_TestCase_test
                ${PROJECT_NAME}
                ole32
                dbgeng
            )
            target_link_libraries (
                ${PROJECT_NAME}_TestSuite_test
                ${PROJECT_NAME}
                ole32
                dbgeng
            )

        elseif (${TESTCPP_STACKTRACE_ENABLED})
            target_link_libraries (
                ${PROJECT_NAME}_TestCase_test
                ${PROJECT_NAME}
                dl
            )
            target_link_libraries (
                ${PROJECT_NAME}_TestSuite_test
                ${PROJECT_NAME}
                dl
            )

        else ()
            target_link_libraries (
                ${PROJECT_NAME}_TestCase_test
                ${PROJECT_NAME}
            )
            target_link_libraries (
                ${PROJECT_NAME}_TestSuite_test
                ${PROJECT_NAME}
            )
        endif ()
    endif ()
endif ()
