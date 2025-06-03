target_include_directories (
    ${PROJECT_NAME} PRIVATE
    include
)

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
        ${PROJECT_NAME}_TestSuite_ctor_test PRIVATE
        test/include
        include
    )
    target_include_directories (
        ${PROJECT_NAME}_TestSuite_running_test PRIVATE
        test/include
        include
    )
    target_include_directories (
        ${PROJECT_NAME}_TestSuite_tpm_test PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_Assertions_basic_test PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_Exceptions_test PRIVATE
        test/include
        include
    )
endif ()
