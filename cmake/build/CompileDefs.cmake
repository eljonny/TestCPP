if (${TESTCPP_STACKTRACE_ENABLED})
    if (MSVC)
        target_compile_definitions (
            ${PROJECT_NAME}
            PUBLIC
                TESTCPP_STACKTRACE_ENABLED
                BOOST_STACKTRACE_USE_WINDBG
        )
    else ()
        find_package (Backtrace)
        if (Backtrace_FOUND)
            set (TESTCPP_INTERNAL_PREFER_BACKTRACE true)
            target_compile_definitions (
                ${PROJECT_NAME}
                PUBLIC
                    TESTCPP_STACKTRACE_ENABLED
                    # We don't know yet if Boost.Stacktrace has
                    #  Backtrace support, we will know during the
                    #  Linking phase and will add this if it does.
                    #BOOST_STACKTRACE_USE_BACKTRACE
            )
        else ()
            set (TESTCPP_INTERNAL_PREFER_BACKTRACE false)
            # See https://github.com/Kitware/CMake/blob/v3.30.2/Modules/CMakeFindBinUtils.cmake
            # Also see https://cmake.org/cmake/help/v3.30/command/find_program.html
            if (DEFINED CMAKE_ADDR2LINE AND NOT (${CMAKE_ADDR2LINE} STREQUAL "CMAKE_ADDR2LINE-NOTFOUND"))
                target_compile_definitions (
                    ${PROJECT_NAME}
                    PUBLIC
                        TESTCPP_STACKTRACE_ENABLED
                        BOOST_STACKTRACE_USE_ADDR2LINE
                )
            else ()
                target_compile_definitions (
                    ${PROJECT_NAME}
                    PUBLIC
                        TESTCPP_STACKTRACE_ENABLED
                )
            endif ()
        endif ()
    endif ()
endif ()
