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
        ${PROJECT_NAME}_TestCase_test
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_TestSuite_ctor_test
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_TestSuite_running_test
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_TestSuite_tpm_test
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_Assertions_basic_test
        PUBLIC
        DEBUG_LOG
    )
    target_compile_definitions (
        ${PROJECT_NAME}_Exceptions_test
        PUBLIC
        DEBUG_LOG
    )
endif ()
