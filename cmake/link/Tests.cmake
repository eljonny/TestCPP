if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
    target_link_libraries (
        ${PROJECT_NAME}_test_TestCase
        ${PROJECT_NAME}
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_ctor
        ${PROJECT_NAME}
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_running
        ${PROJECT_NAME}
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_tpm
        ${PROJECT_NAME}
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Assertions_basic
        ${PROJECT_NAME}
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Exceptions
        ${PROJECT_NAME}
        ole32
        dbgeng
    )

elseif (${TESTCPP_STACKTRACE_ENABLED})
    target_link_libraries (
        ${PROJECT_NAME}_test_TestCase
        ${PROJECT_NAME}
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_ctor
        ${PROJECT_NAME}
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_running
        ${PROJECT_NAME}
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_tpm
        ${PROJECT_NAME}
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Assertions_basic
        ${PROJECT_NAME}
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Exceptions
        ${PROJECT_NAME}
        dl
    )

else ()
    target_link_libraries (
        ${PROJECT_NAME}_test_TestCase
        ${PROJECT_NAME}
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_ctor
        ${PROJECT_NAME}
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_running
        ${PROJECT_NAME}
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_TestSuite_tpm
        ${PROJECT_NAME}
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Assertions_basic
        ${PROJECT_NAME}
    )
    target_link_libraries (
        ${PROJECT_NAME}_test_Exceptions
        ${PROJECT_NAME}
    )
endif ()
