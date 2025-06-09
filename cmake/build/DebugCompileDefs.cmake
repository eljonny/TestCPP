target_compile_definitions (
    ${PROJECT_NAME}
    PUBLIC
    DEBUG_LOG
)

if (${TESTCPP_DEMO_ENABLED})
    target_compile_definitions (
        ${PROJECT_NAME}_run
        PUBLIC
        DEBUG_LOG
    )
endif ()

if (BUILD_TESTING)
    target_compile_definitions (
        ${PROJECT_NAME}_test_TestCase
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_test_TestSuite_ctor
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_test_TestSuite_running
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_test_TestSuite_tpm
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_test_Assertions_basic
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_test_Exceptions
        PUBLIC
        DEBUG_LOG
    )
endif ()
