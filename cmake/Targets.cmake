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
        ${PROJECT_NAME}_test_TestCase
        test/src/TestCase/TestCaseTests.cpp
        test/src/TestCase/TestCaseTestChunks.cpp
        test/src/TestCPPTestCaseMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_test_TestSuite_ctor
        test/src/TestSuite/TestSuiteConstructionTests.cpp
        test/src/TestCPPTestSuiteConstructionMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_test_TestSuite_running
        test/src/TestSuite/TestSuiteRunningTests.cpp
        test/src/TestCPPTestSuiteRunningMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_test_TestSuite_tpm
        test/src/TestSuite/TestSuiteTestPassedMessageTests.cpp
        test/src/TestCPPTestSuiteTestPassedMessageMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_test_Assertions_basic
        test/src/Assertions/AssertionsBasicTests.cpp
        test/src/TestCPPAssertionsBasicMain.cpp
    )

    add_executable (
        ${PROJECT_NAME}_test_Exceptions
        test/src/Exceptions/ExceptionsTests.cpp
        test/src/TestCPPExceptionsMain.cpp
    )
endif ()
