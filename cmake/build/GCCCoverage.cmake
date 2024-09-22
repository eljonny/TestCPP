list (
    APPEND
    COVERAGE_BUILD_OPTS
    -g               # Enable all debugging information.
    -Og              # Ensure the compiler doesn't use optimizations
                     #  that would harm debuggability of the resulting
                     #  code.
    -Wall            # Enable most warnings.
    -Wextra          # Enable even more warnings.
    -Wpedantic       # Enable most of the rest of the warnings.
    -Werror          # Treat all warnings as errors.
    -fprofile-arcs   # Enable profile points that help with code
                     #  coverage.
    -ftest-coverage  # Enable core code coverage compilation.
)

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

target_compile_options (
    ${PROJECT_NAME}_Assertions_test
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)
