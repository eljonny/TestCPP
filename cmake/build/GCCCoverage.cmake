list (
    APPEND
    COVERAGE_BUILD_OPTS
    -g                          # Enable all debugging information.
    -Og                         # Ensure the compiler doesn't use
                                #  optimizations that would harm
                                #  debuggability of the resulting code.
    -Wall                       # Enable most warnings.
    -Wextra                     # Enable even more warnings.
    -Wpedantic                  # Enable most of the rest of the
                                #  warnings.
    -Werror                     # Treat all warnings as errors.
    -Wno-c++98-compat           # We're compiling for C++11, so it's not
                                #  necessary to maintain compatibility
                                #  with C++98.
    -Wno-c++98-compat-pedantic  # We're compiling for C++11, so, again,
                                #  it's not necessary to maintain
                                #  compatibility with C++98.
    -Wno-covered-switch-default # -Wswitch-default is more important.
    -fprofile-arcs              # Enable profile points that help with
                                #  code coverage.
    -ftest-coverage             # Enable core code coverage compilation.
)

# Add -Wno-global-constructors to the GCC build options after it exists
#  like in GCCClangRelease.cmake and GCCClangDebug.cmake.
# Ref https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71482

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

target_compile_options (
    ${PROJECT_NAME}_Exceptions_test
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)
