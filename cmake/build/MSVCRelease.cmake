list (
    APPEND
    MSVC_RELEASE_BUILD_OPTS

    /nologo                 # Suppress the compiler version and
                            #  copyright information.
    /EHsc                   # Enable C++ exceptions.
    /Wall                   # Enable all warnings and treat them as
                            #  errors.
    /WX                     # Treat linker warnings as errors also.
    /O2                     # Do optimizations for the Release build.
    /wd4710                 # It's ok if functions are not inlined.
    /wd4711                 # It's also ok if functions are inlined.
    /wd4820                 # Struct/class data member padding is ok,
                            #  we're concerned about speed, not space,
                            #  and the natural alignment is generally
                            #  fastest.
                            # Let the compiler add the padding.
    /wd4100                 # Unused parameters occur in the Release
                            #  build in debugLog.
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
        MSVC_RELEASE_BUILD_OPTS

        # Include the 3rdparty dependency directories as external.
        "/external:I3rdparty/boost.assert/include"
        "/external:I3rdparty/boost.config/include"
        "/external:I3rdparty/boost.container_hash/include"
        "/external:I3rdparty/boost.core/include"
        "/external:I3rdparty/boost.describe/include"
        "/external:I3rdparty/boost.mp11/include"
        "/external:I3rdparty/boost.predef/include"
        "/external:I3rdparty/boost.stacktrace/include"
        "/external:I3rdparty/boost.static_assert/include"
        "/external:I3rdparty/boost.throw_exception/include"
        "/external:I3rdparty/boost.winapi/include"
    )
endif ()

target_compile_options (
    ${PROJECT_NAME}
    PUBLIC
    ${MSVC_RELEASE_BUILD_OPTS}
)

if (${TESTCPP_DEMO_ENABLED})
    target_compile_options (
        ${PROJECT_NAME}_run
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )
endif ()

if (BUILD_TESTING)
    target_compile_options (
        ${PROJECT_NAME}_TestCase_test
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_TestSuite_ctor_test
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_TestSuite_running_test
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_TestSuite_tpm_test
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_Assertions_basic_test
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_Exceptions_test
        PUBLIC
        ${MSVC_RELEASE_BUILD_OPTS}
    )
endif ()

# This section removes the /RTC flags from the CMAKE_CXX_FLAGS_*
#  variables, because CMake is automatically adding them to the
#  generated VS MSBuild builds without me specifying them,
#  specifically because they should not be in a Release build.
foreach (flag_var
         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    STRING (REGEX REPLACE "[/\-]RTC[1csu]*" "" ${flag_var} "${${flag_var}}")
endforeach (flag_var)
