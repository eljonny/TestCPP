list (
    APPEND
    GCC_CLANG_RELEASE_BUILD_OPTS
    -O3                         # Optimize the Release build.
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
    -Wno-unused-parameter       # Unused parameters occur in the Release
                                #  build in debugLog.
    -Wno-unused-lambda-capture  # Avoid MSVC error C3493 - There is
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

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_VS_PLATFORM_TOOLSET}" STREQUAL "ClangCL")

    # GCC doesn't support -Wno-global-constructors yet, so only add it
    #  if we are building with Clang, either with MSVC as a frontend
    #  or straight-up LLVM.
    # Ref https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71482

    list (
        APPEND
        GCC_CLANG_RELEASE_BUILD_OPTS
        -Wno-global-constructors # The performance degradation pointed
                                 #  out by this warning is non-trivial
                                 #  but not enough to work through any
                                 #  issues that might be caused by it;
                                 #  there were already constructors
                                 #  from built-in types that were being
                                 #  called (particularly unique_ptr),
                                 #  but this points out that the type I
                                 #  added (no_destroy) adds custom and
                                 #  additional start-up code that can
                                 #  change startup performance by
                                 #  making it slower.
                                 # How much slower is a matter of
                                 #  micro-optimization for this library
                                 #  project in particular, but could
                                 #  significantly decrease startup
                                 #  performance if there were n-many of
                                 #  these objects being created.
                                 # At this point there are only 6, so
                                 #  this should not cause a noticeable
                                 #  hit to startup performance.
    )
endif ()

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

    target_compile_options (
        ${PROJECT_NAME}_Exceptions_test
        PUBLIC
        ${GCC_CLANG_RELEASE_BUILD_OPTS}
    )
endif ()
