if (BUILD_TESTING)
    add_test (
        NAME ${PROJECT_NAME}TestCaseTests
        COMMAND ${PROJECT_NAME}_test_TestCase
    )

    add_test (
        NAME ${PROJECT_NAME}TestSuiteConstructionTests
        COMMAND ${PROJECT_NAME}_test_TestSuite_ctor
    )
    add_test (
        NAME ${PROJECT_NAME}TestSuiteRunningTests
        COMMAND ${PROJECT_NAME}_test_TestSuite_running
    )
    add_test (
        NAME ${PROJECT_NAME}TestSuiteTestPassedMessageTests
        COMMAND ${PROJECT_NAME}_test_TestSuite_tpm
    )

    add_test (
        NAME ${PROJECT_NAME}AssertionsBasicTests
        COMMAND ${PROJECT_NAME}_test_Assertions_basic
    )

    add_test (
        NAME ${PROJECT_NAME}ExceptionsTests
        COMMAND ${PROJECT_NAME}_test_Exceptions
    )
endif ()
