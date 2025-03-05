if (BUILD_TESTING)
    add_test (
        NAME ${PROJECT_NAME}TestCaseTests
        COMMAND ${PROJECT_NAME}_TestCase_test
    )

    add_test (
        NAME ${PROJECT_NAME}TestSuiteConstructionTests
        COMMAND ${PROJECT_NAME}_TestSuite_ctor_test
    )
    add_test (
        NAME ${PROJECT_NAME}TestSuiteRunningTests
        COMMAND ${PROJECT_NAME}_TestSuite_running_test
    )
    add_test (
        NAME ${PROJECT_NAME}TestSuiteTestPassedMessageTests
        COMMAND ${PROJECT_NAME}_TestSuite_tpm_test
    )

    add_test (
        NAME ${PROJECT_NAME}AssertionsBasicTests
        COMMAND ${PROJECT_NAME}_Assertions_basic_test
    )

    add_test (
        NAME ${PROJECT_NAME}ExceptionsTests
        COMMAND ${PROJECT_NAME}_Exceptions_test
    )
endif ()
