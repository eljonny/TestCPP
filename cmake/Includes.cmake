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
        ${PROJECT_NAME}_test_TestCase PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_test_TestSuite_ctor PRIVATE
        test/include
        include
    )
    target_include_directories (
        ${PROJECT_NAME}_test_TestSuite_running PRIVATE
        test/include
        include
    )
    target_include_directories (
        ${PROJECT_NAME}_test_TestSuite_tpm PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_test_Assertions_basic PRIVATE
        test/include
        include
    )

    target_include_directories (
        ${PROJECT_NAME}_test_Exceptions PRIVATE
        test/include
        include
    )
endif ()
