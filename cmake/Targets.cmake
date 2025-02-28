add_library (
    ${PROJECT_NAME}
    src/TestCPPAssertions.cpp
    src/TestCPPExceptions.cpp
    src/TestCPPTestCase.cpp
    src/TestCPPTestSuite.cpp
    src/TestCPPUtil.cpp
)

add_library (
    ${PROJECT_GROUP_NAME}::${PROJECT_NAME}
    ALIAS
        ${PROJECT_NAME}
)

if (${TESTCPP_DEMO_ENABLED})
    add_executable (
        ${PROJECT_NAME}_run
        demo/src/tests.cpp
        demo/src/main.cpp
    )
endif ()

if (BUILD_TESTING)
    add_executable (
        ${PROJECT_NAME}_TestCase_test
        test/src/TestCase/TestCaseTests.cpp
        test/src/TestCase/TestCaseTestChunks.cpp
        test/src/TestCPPTestCaseMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_TestSuite_test
        test/src/TestSuite/TestSuiteTests.cpp
        test/src/TestCPPTestSuiteMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_Assertions_test
        test/src/Assertions/BasicAssertionsTests.cpp
        test/src/TestCPPAssertionsMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_Exceptions_test
        test/src/Exceptions/ExceptionsTests.cpp
        test/src/TestCPPExceptionsMain.cpp
    )
endif ()
