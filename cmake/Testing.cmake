if (BUILD_TESTING)
    add_test (
        NAME ${PROJECT_NAME}TestCaseTests
        COMMAND ${PROJECT_NAME}_TestCase_test
    )

    add_test (
        NAME ${PROJECT_NAME}TestSuiteTests
        COMMAND ${PROJECT_NAME}_TestSuite_test
    )
endif ()
