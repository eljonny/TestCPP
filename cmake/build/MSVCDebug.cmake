list (
    APPEND
    MSVC_DEBUG_BUILD_OPTS

    /nologo                 # Suppress the compiler version and
                            #  copyright information.
    /Zi                     # Generate complete debugging information.
    /FS                     # Force synchronous PDB writes.
    /EHscr                  # Enable C++ exceptions, including RTCs for
                            #  noexcept verification at runtime.
    /RTC1                   # Enable Runtime Checks.
    /Wall                   # Enable all warnings and treat them as
                            #  errors.
    /WX                     # Treat linker warnings as errors also.
    /Od                     # Perform no optimization; the resulting
                            #  code is optimized for debugging and
                            #  debuggability.
    /wd4820                 # Struct/class data member padding is ok,
                            #  we're concerned about speed, not space,
                            #  and the natural alignment is generally
                            #  fastest.
                            # Let the compiler add the padding.
    /wd5045                 # Warns about code that can cause the
                            #  Spectre vulnerability to become
                            #  exploitable, does not go away when
                            #  /Qspectre is specified.
                            # Applied this warning suppression since
                            #  /Qspectre is specified.
    /Qspectre               # Instructs the compiler to apply Spectre
                            #  vulnerability mitigations.
    /external:anglebrackets # Treat angle-bracket includes as system
                            #  includes.
    /external:W0            # Suppress all warnings from external
                            #  headers.
)

if (${TESTCPP_STACKTRACE_ENABLED})
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS

        "/external:I3rdparty/include" # Include the 3rdparty directory
                                      #  as an external include
                                      #  directory.
    )
endif ()

if ("${CMAKE_CXX_FLAGS}" MATCHES "/analyze:ruleset")
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS

        /analyze:rulesetdirectory "${VS_INSTALLATION_PATH}/Team Tools/Static Analysis Tools/Rule Sets"
    )
endif ()

target_compile_options (
    ${PROJECT_NAME}
    PUBLIC
    ${MSVC_DEBUG_BUILD_OPTS}
)

if (${TESTCPP_DEMO_ENABLED})
    target_compile_options (
        ${PROJECT_NAME}_run
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
endif ()

if (BUILD_TESTING)
    target_compile_options (
        ${PROJECT_NAME}_TestCase_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_TestSuite_ctor_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_TestSuite_running_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_TestSuite_tpm_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_Assertions_basic_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_Exceptions_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
endif ()
