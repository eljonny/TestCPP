if (${TESTCPP_STACKTRACE_ENABLED})
    target_include_directories (
        ${PROJECT_NAME} PRIVATE
        3rdparty/include
        include
    )

else ()
    target_include_directories (
        ${PROJECT_NAME} PRIVATE
        include
    )
endif ()

if (${TESTCPP_DEMO_ENABLED})
    target_include_directories (
        ${PROJECT_NAME}_run PRIVATE
        demo/include
        include
    )
endif ()

if (BUILD_TESTING)
    target_include_directories (
        ${PROJECT_NAME}_TestCase_test PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_TestSuite_test PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_Assertions_test PRIVATE
        test/include
        include
    )
endif ()
