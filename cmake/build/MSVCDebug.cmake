list (
    APPEND
    MSVC_DEBUG_BUILD_OPTS

    /nologo                 # Suppress the compiler version and
                            #  copyright information.
    /Zi                     # Generate complete debugging information.
    /FS                     # Force synchronous PDB writes.
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
    /external:W0            # Suppress all warnings from external
                            #  headers.
)

if (${TESTCPP_STACKTRACE_ENABLED})
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS

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

if ("${CMAKE_CXX_FLAGS}" MATCHES "/analyze:ruleset")
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS

        /analyze:rulesetdirectory "${VS_INSTALLATION_PATH}/Team Tools/Static Analysis Tools/Rule Sets"
    )
endif ()

if (NOT ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS

        /EHscr                  # Enable C++ exceptions, including RTCs
                                #  for noexcept verification at
                                #  runtime, only if using CL.
        /Qspectre               # Instructs the compiler to apply
                                #  Spectre vulnerability mitigations.
        /external:anglebrackets # Treat angle-bracket includes as
                                #  system includes.
    )
else ()
    # If using clang-cl, we need some additional/altered flags
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS

        /EHsc                      # Enable C++ exceptions, without
                                   #  RTCs for noexcept verification at
                                   #  runtime; clang-cl does not
                                   #  support /EHscr.
        -Wno-c++98-compat          # We're compiling for C++11, so it's
                                   #  not necessary to maintain
                                   #  compatibility with C++98.
        -Wno-c++98-compat-pedantic # We're compiling for C++11, so,
                                   #  again, it's not necessary to
                                   #  maintain compatibility with
                                   #  C++98.
        -Wno-global-constructors   # The performance degradation
                                   #  pointed out by this warning is
                                   #  non-trivial but not enough to
                                   #  work through any issues that
                                   #  might be caused by it; there were
                                   #  already constructors from built-
                                   #  in types that were being called
                                   #  (particularly unique_ptr), but
                                   #  this points out that the type I
                                   #  added (no_destroy) adds custom
                                   #  and additional start-up code that
                                   #  can change startup performance by
                                   #  making it slower.
                                   # How much slower is a matter of
                                   #  micro-optimization for this
                                   #  library project in particular,
                                   #  but could significantly decrease
                                   #  startup performance if there were
                                   #  n-many of these objects being
                                   #  created.
                                   # At this point there are only 6, so
                                   #  this should not cause a
                                   #  noticeable hit to startup
                                   #  performance.
    )

    if (NOT (${TESTCPP_STACKTRACE_ENABLED}))
        # If stack traces are enabled, we use C++14 features that make
        #  this warning suppression unnecessary, so we don't add it
        #  unless we need it.
        list (
            APPEND
            MSVC_DEBUG_BUILD_OPTS

            -Wno-unused-lambda-capture # Avoid MSVC error C3493 - There
                                       #  is implementation divergence
                                       #  here and since we're not
                                       #  using >=C++14 there is no
                                       #  workaround other than to
                                       #  ignore this warning (the MSVC
                                       #  issue is an error).
                                       # A workaround for >=C++14 is to
                                       #  use an explicit capture.
        )
    endif ()

    if (BUILD_TESTING)
        list (
            APPEND
            MSVC_DEBUG_TEST_BUILD_OPTS

            ${MSVC_DEBUG_BUILD_OPTS}
            -Wno-undefined-func-template # Not a real problem
            -Wno-exit-time-destructors   # This is not a concern for
                                         #  test executables in this
                                         #  project, it's a single
                                         #  object that gets destroyed.
        )
    endif ()
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

if (BUILD_TESTING AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    target_compile_options (
        ${PROJECT_NAME}_test_TestCase
        PUBLIC
        ${MSVC_DEBUG_TEST_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_test_TestSuite_ctor
        PUBLIC
        ${MSVC_DEBUG_TEST_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_test_TestSuite_running
        PUBLIC
        ${MSVC_DEBUG_TEST_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_test_TestSuite_tpm
        PUBLIC
        ${MSVC_DEBUG_TEST_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_test_Assertions_basic
        PUBLIC
        ${MSVC_DEBUG_TEST_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_test_Exceptions
        PUBLIC
        ${MSVC_DEBUG_TEST_BUILD_OPTS}
    )
elseif (BUILD_TESTING)
    target_compile_options (
        ${PROJECT_NAME}_test_TestCase
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_test_TestSuite_ctor
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_test_TestSuite_running
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
    target_compile_options (
        ${PROJECT_NAME}_test_TestSuite_tpm
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_test_Assertions_basic
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_test_Exceptions
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
endif ()
