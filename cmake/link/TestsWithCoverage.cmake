if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
    target_link_libraries (
        ${PROJECT_NAME}_test_TestCase
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_ctor
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_running
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_tpm
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Assertions_basic
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Exceptions
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )

elseif (${TESTCPP_STACKTRACE_ENABLED})
    target_link_libraries (
        ${PROJECT_NAME}_test_TestCase
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_ctor
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_running
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_tpm
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Assertions_basic
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Exceptions
        ${PROJECT_NAME}
        gcov
        dl
    )

else ()
    target_link_libraries (
        ${PROJECT_NAME}_test_TestCase
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_ctor
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_running
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_tpm
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Assertions_basic
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Exceptions
        ${PROJECT_NAME}
        gcov
    )
endif ()
