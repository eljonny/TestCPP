if (BUILD_TESTING)
    add_test (
        NAME ${PROJECT_NAME}TestCaseTests
        COMMAND ${PROJECT_NAME}_TestCase_test
    )

    add_test (
        NAME ${PROJECT_NAME}TestSuiteTests
        COMMAND ${PROJECT_NAME}_TestSuite_test
    )

    add_test (
        NAME ${PROJECT_NAME}AssertionsTests
        COMMAND ${PROJECT_NAME}_Assertions_test
    )

    add_test (
        NAME ${PROJECT_NAME}ExceptionsTests
        COMMAND ${PROJECT_NAME}_Exceptions_test
    )
endif ()
