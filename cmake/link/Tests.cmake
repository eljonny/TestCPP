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
    target_link_libraries (
        ${PROJECT_NAME}_Assertions_test
        ${PROJECT_NAME}
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_Exceptions_test
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
    target_link_libraries (
        ${PROJECT_NAME}_Assertions_test
        ${PROJECT_NAME}
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_Exceptions_test
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
    target_link_libraries (
        ${PROJECT_NAME}_Assertions_test
        ${PROJECT_NAME}
    )
    target_link_libraries (
        ${PROJECT_NAME}_Exceptions_test
        ${PROJECT_NAME}
    )
endif ()
