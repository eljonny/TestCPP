include (SubmodulesInit)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/boost.stacktrace"
    "${CMAKE_CURRENT_BINARY_DIR}/boost.stacktrace"
    EXCLUDE_FROM_ALL
)

list(
    APPEND
    BOOST_STACKTRACE_DEPS

    assert
    static_assert
    throw_exception
    config
    container_hash
    core
    describe
    mp11
    predef
    winapi
)

foreach(B_ST_DEP IN LISTS BOOST_STACKTRACE_DEPS)
    list (
        APPEND
        BOOST_STACKTRACE_EXPORTS_LIST
        boost_${B_ST_DEP}
    )
    add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/boost.${B_ST_DEP}"
        "${CMAKE_CURRENT_BINARY_DIR}/boost.${B_ST_DEP}"
        EXCLUDE_FROM_ALL
    )
endforeach()

list (
    APPEND
    BOOST_STACKTRACE_EXPORTS_LIST

    boost_stacktrace
)

# Use WinDbg for Windows
if (MSVC)
    list (
        APPEND
        BOOST_STACKTRACE_EXPORTS_LIST

        boost_stacktrace_windbg
    )
    target_link_libraries(
        ${PROJECT_NAME}
        ole32
        dbgeng
        Boost::stacktrace_windbg
    )
# Use the most powerful choices first for Linux, and if not available fall back to others.
# First try Backtrace for Linux, then addr2line, and finally the default Boost.Stacktrace.
else ()
    find_package (Backtrace)
    if ((${BOOST_STACKTRACE_HAS_BACKTRACE}) AND (DEFINED Backtrace_FOUND))
        list (
            APPEND
            BOOST_STACKTRACE_EXPORTS_LIST

            boost_stacktrace_backtrace
        )
        target_link_libraries(
            ${PROJECT_NAME}
            dl
            backtrace
            Boost::stacktrace_backtrace
        )
    else ()
        # See https://github.com/Kitware/CMake/blob/v3.30.2/Modules/CMakeFindBinUtils.cmake
        # Also see https://cmake.org/cmake/help/v3.30/command/find_program.html
        if (DEFINED CMAKE_ADDR2LINE AND NOT (${CMAKE_ADDR2LINE} STREQUAL "CMAKE_ADDR2LINE-NOTFOUND"))
            list (
                APPEND
                BOOST_STACKTRACE_EXPORTS_LIST

                boost_stacktrace_addr2line
            )
            target_link_libraries(
                ${PROJECT_NAME}
                dl
                Boost::stacktrace_addr2line
            )
        else ()
            target_link_libraries(
                ${PROJECT_NAME}
                Boost::stacktrace_basic
            )
        endif ()
    endif ()
endif ()
