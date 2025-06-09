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
    -Wno-unknown-pragmas        # Ignore unknown pragmas, since we are
                                #  building for Clang, GCC, and MSVC,
                                #  and MSVC has different pragmas than
                                #  GCC/Clang.
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
    ${PROJECT_NAME}_test_TestCase
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)

target_compile_options (
    ${PROJECT_NAME}_test_TestSuite_ctor
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)
target_compile_options (
    ${PROJECT_NAME}_test_TestSuite_running
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)
target_compile_options (
    ${PROJECT_NAME}_test_TestSuite_tpm
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)

target_compile_options (
    ${PROJECT_NAME}_test_Assertions_basic
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)

target_compile_options (
    ${PROJECT_NAME}_test_Exceptions
    PUBLIC
    ${COVERAGE_BUILD_OPTS}
)
