if (${TESTCPP_STACKTRACE_ENABLED})
    target_compile_definitions (
        ${PROJECT_NAME}
        PUBLIC
        TESTCPP_STACKTRACE_ENABLED
    )
endif ()
