list (
    APPEND
    GCC_CLANG_RELEASE_BUILD_OPTS
    -O3                        # Optimize the Release build.
    -Wall                      # Enable most warnings.
    -Wextra                    # Enable even more warnings.
    -Wpedantic                 # Enable most of the rest of the
                               #  warnings.
    -Werror                    # Treat all warnings as errors.
    -Wno-unused-parameter      # Unused parameters occur in the Release
                               #  build in debugLog.
    -Wno-unused-lambda-capture # Avoid MSVC error C3493 - There is
                               #  implementation divergence here and
                               #  since we're not using >=C++14 there
                               #  is no workaround other than to ignore
                               #  this warning (the MSVC issue is an
                               #  error).
                               # A workaround for >=C++14 is to use an
                               #  explicit capture - if ever I change
                               #  the library to use >=C++14 I can
                               #  remove this and use an explicit
                               #  capture.
)

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

    target_compile_options (
        ${PROJECT_NAME}_Assertions_test
        PUBLIC
        ${GCC_CLANG_RELEASE_BUILD_OPTS}
    )
endif ()
