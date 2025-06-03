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
)

if (MSVC)
    list(
        APPEND
        BOOST_STACKTRACE_DEPS

        winapi
    )
endif ()

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

if (MSVC)
    list (
        APPEND
        BOOST_STACKTRACE_EXPORTS_LIST

        boost_stacktrace_windbg
    )
else ()
    FindBacktrace()
    if (Backtrace_FOUND)
        list (
            APPEND
            BOOST_STACKTRACE_EXPORTS_LIST

            boost_stacktrace_backtrace
        )
    endif ()

    FindBinUtils()
    if (NOT CMAKE_ADDR2LINE-NOTFOUND)
        list (
            APPEND
            BOOST_STACKTRACE_EXPORTS_LIST

            boost_stacktrace_addr2line
        )
    endif ()
endif ()

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        Boost::stacktrace
)
