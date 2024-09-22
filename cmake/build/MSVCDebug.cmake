
list (
    APPEND
    MSVC_DEBUG_BUILD_OPTS
    /Wall     # Enable all warnings and treat them as errors.
    /WX       # Treat linker warnings as errors also.
    /Od       # Perform no optimization; the resulting code is optimized
              #  for debugging and debuggability.
    /wd4820   # Struct/class data member padding is ok, we're concerned
              #  about speed, not space, and the natural alignment is
              #  generally fastest.
              # Let the compiler add the padding.
    /wd4668   # There are undefined preprocessor macros in the Windows
              #  SDK in internal headers.
              # This is a workaround until these issues are fixed by
              #  Microsoft.
    /wd5045   # Warns about code that can cause the Spectre
              #  vulnerability to become exploitable, does not go away
              #  when /Qspectre is specified.
              # Applied this warning suppression since /Qspectre is
              #  specified.
    /Qspectre # Instructs the compiler to apply Spectre vulnerability
              #  mitigations.
)

if (${TESTCPP_STACKTRACE_ENABLED})
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS
        /wd5039 # There's a function or two in the Windows SDK that is/
                #  are passed to extern 'C' APIs that are not marked as
                #  noexcept which causes this warning, which is treated
                #  as an error.
                # There's nothing we can do about this so this is added
                #  as a workaround.
        /wd4625 # In the Boost.StackTrace code, there are copy
                #  constructors that are implicitly deleted.
                # Since this is in an external library, suppress the
                #  warning to work around this to ensure clean
                #  compilation.
        /wd4626 # In the Boost.StackTrace code, there are copy
                #  assignment operators that are implicitly deleted.
                # Since this is in an external library, suppress the
                #  warning to work around this to ensure clean
                #  compilation.
        /wd5026 # In the Boost.StackTrace code, there are move
                #  constructors that are implicitly deleted.
                # Since this is in an external library, suppress the
                #  warning to work around this to ensure clean
                #  compilation.
        /wd5027 # In the Boost.StackTrace code, there are move
                #  assignment operators that are implicitly deleted.
                # Since this is in an external library, suppress the
                #  warning to work around this to ensure clean
                #  compilation.
    )
endif ()

if (BUILD_TESTING)
    list (
        APPEND
        MSVC_DEBUG_BUILD_OPTS
        /wd4514 # It's ok if the compiler removes unreferenced inline
                #  functions.
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
        ${PROJECT_NAME}_TestSuite_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )

    target_compile_options (
        ${PROJECT_NAME}_Assertions_test
        PUBLIC
        ${MSVC_DEBUG_BUILD_OPTS}
    )
endif ()
