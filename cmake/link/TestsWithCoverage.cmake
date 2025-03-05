if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
    target_link_libraries (
        ${PROJECT_NAME}_TestCase_test
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_ctor_test
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_running_test
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_tpm_test
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_Assertions_basic_test
        ${PROJECT_NAME}
        gcov
        ole32
        dbgeng
    )
    target_link_libraries (
        ${PROJECT_NAME}_Exceptions_test
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
        ${PROJECT_NAME}_TestSuite_ctor_test
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_running_test
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_tpm_test
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_Assertions_basic_test
        ${PROJECT_NAME}
        gcov
        dl
    )
    target_link_libraries (
        ${PROJECT_NAME}_Exceptions_test
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
        ${PROJECT_NAME}_TestSuite_ctor_test
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_running_test
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_TestSuite_tpm_test
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_Assertions_basic_test
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_Exceptions_test
        ${PROJECT_NAME}
        gcov
    )
endif ()
