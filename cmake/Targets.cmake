add_library (
    ${PROJECT_NAME}
    src/TestUtil.cpp
    src/Test.cpp
)
add_library (
    ${PROJECT_GROUP_NAME}::${PROJECT_NAME}
    ALIAS
        ${PROJECT_NAME}
)

if (${CMAKE_DEMO_ENABLED})
    add_executable (
        ${PROJECT_NAME}_run
        demo/src/main.cpp
    )
endif ()

if (BUILD_TESTING)
    add_executable (
        ${PROJECT_NAME}_TestCase_test
        test/src/TestCase/TestCaseTestChunks.cpp
        test/src/TestCPPTestCaseMain.cpp
    )
    
    add_executable (
        ${PROJECT_NAME}_TestSuite_test
        test/src/TestCPPTestSuiteMain.cpp
    )
endif ()
