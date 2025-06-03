if (${TESTCPP_STACKTRACE_ENABLED})
    if (MSVC AND ("${CMAKE_VS_PLATFORM_TOOLSET}" STREQUAL "ClangCL"))
        target_compile_definitions (
            ${PROJECT_NAME}
            PUBLIC
                TESTCPP_STACKTRACE_ENABLED
                BOOST_STACKTRACE_USE_WINDBG
        )
    else ()
        target_compile_definitions (
            ${PROJECT_NAME}
            PUBLIC
                TESTCPP_STACKTRACE_ENABLED
        )
    endif ()
endif ()
