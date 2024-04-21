list (
    APPEND
    MSVC_RELEASE_BUILD_OPTS
    /Wall     # Enable all warnings and treat them as errors
    /WX       # Treat linker warnings as errors also
    /O2       # Do optimizations for the Release build
    /wd4668   # There are undefined preprocessor macros in the Windows
              #  SDK in internal headers. This is a workaround until
              #  these issues are fixed by Microsoft.
    /wd4710   # It's ok if functions are not inlined
    /wd4711   # It's also ok if functions are inlined
    /wd4820   # Struct/class data member padding is ok, we're concerned
              #  about speed, not space, and the natural alignment
              #  is generally fastest. Let the compiler add the padding.
    /wd4100   # Unused parameters occur in the Release build in debugLog
    /wd5045   # Warns about code that can cause the Spectre
              #  vulnerability to become exploitable, does not
              #  go away when /Qspectre is specified. Applied this
              #  warning suppression since /Qspectre is specified.
    /Qspectre # Instructs the compiler to apply Spectre
              #  vulnerability mitigations.
)
list (
    APPEND
    MSVC_DEBUG_BUILD_OPTS 
    /Wall /WX /Od
    /wd4820 /wd4668 /wd5045
    /Qspectre
)

if (${TESTCPP_STACKTRACE_ENABLED})
    list (
        APPEND
        MSVC_RELEASE_BUILD_OPTS
        /wd5039 # There's a function or two in the Windows SDK that are
                #  passed to extern 'C' APIs that are not marked as
                #  noexcept which causes this warning, which is treated
                #  as an error. There's nothing we can do about this so
                #  this is added as a workaround.
        /wd4625 # In the Boost.StackTrace code, there are copy
                #  constructors that are implicitly deleted. Since this
                #  is in an external library, suppress the warning to
                #  work around this to ensure clean compilation.
        /wd4626 # In the Boost.StackTrace code, there are copy
                #  assignment operators that are implicitly deleted.
                #  Since this is in an external library, suppress the
                #  warning to work around this to ensure clean
                #  compilation.
        /wd5026 # In the Boost.StackTrace code, there are move
                #  constructors that are implicitly deleted. Since this
                #  is in an external library, suppress the warning to
                #  work around this to ensure clean compilation.
        /wd5027 # In the Boost.StackTrace code, there are move
                #  assignment operators that are implicitly deleted.
                #  Since this is in an external library, suppress the
                #  warning to work around this to ensure clean
                #  compilation.
    )
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS 
        /wd5039 /wd4625 /wd4626 /wd5026 /wd5027
    )
endif ()

if (BUILD_TESTING)
    list (
        APPEND
        MSVC_RELEASE_BUILD_OPTS
        /wd4514 # It's ok if the compiler removes unreferenced inline
                #  functions.
    )
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS
        /wd4514
    )
endif ()

list (
    APPEND
    GCC_CLANG_RELEASE_BUILD_OPTS
    -O3                   # Optimize the Release build
    -Wall                 # Enable most warnings
    -Wextra               # Enable even more warnings
    -Wpedantic            # Enable most of the rest of the warnings
    -Werror               # Treat all warnings as errors
    -Wno-unused-parameter # Unused parameters occur in the Release
                          #  build in debugLog
)
list (
    APPEND
    GCC_CLANG_DEBUG_BUILD_OPTS
    -g  # Enable all debugging information
    -Og # Ensure the compiler doesn't use optimizations that would harm
        #  debuggability of the resulting code
    -Wall -Wextra -Wpedantic -Werror
)
list (
    APPEND
    COVERAGE_BUILD_OPTS
    -g -Og -Wall -Wextra -Wpedantic -Werror
    -fprofile-arcs   # Enable profile points that help with code
                     #  coverage
    -ftest-coverage  # Enable core code coverage compilation
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message (STATUS "Release build compilation options enabled")

    if (MSVC)
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
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${MSVC_RELEASE_BUILD_OPTS}
            )
        endif ()

    else ()
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            ${GCC_CLANG_RELEASE_BUILD_OPTS}
        )

        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                ${GCC_CLANG_RELEASE_BUILD_OPTS}
            )
        endif ()

        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                ${GCC_CLANG_RELEASE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${GCC_CLANG_RELEASE_BUILD_OPTS}
            )
        endif ()
    endif ()

else ()
    message (STATUS "Debug build compilation options enabled")

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
            ${PROJECT_NAME}_TestSuite_test
            PUBLIC
            DEBUG_LOG
        )
    endif ()

    if (MSVC)
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
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${MSVC_DEBUG_BUILD_OPTS}
            )
        endif ()

    else ()
        if (${TESTCPP_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                ${GCC_CLANG_DEBUG_BUILD_OPTS}
            )
        endif ()

        if (BUILD_TESTING AND ${TESTCPP_COVERAGE_ENABLED})
            message (STATUS "Coverage compilation options enabled")

            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                ${COVERAGE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                ${COVERAGE_BUILD_OPTS}
            )

            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                ${COVERAGE_BUILD_OPTS}
            )

        else ()
            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                ${GCC_CLANG_DEBUG_BUILD_OPTS}
            )
        endif ()
    endif ()
endif ()

if (${TESTCPP_STACKTRACE_ENABLED})
    target_compile_definitions (
        ${PROJECT_NAME}
        PUBLIC
        TESTCPP_STACKTRACE_ENABLED
    )
endif ()
