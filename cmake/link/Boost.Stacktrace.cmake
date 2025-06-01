add_subdirectory(3rdparty/boost.assert)
add_subdirectory(3rdparty/boost.config)
add_subdirectory(3rdparty/boost.container_hash)
add_subdirectory(3rdparty/boost.core)
add_subdirectory(3rdparty/boost.describe)
add_subdirectory(3rdparty/boost.mp11)
add_subdirectory(3rdparty/boost.predef)
add_subdirectory(3rdparty/boost.stacktrace)
add_subdirectory(3rdparty/boost.static_assert)
add_subdirectory(3rdparty/boost.throw_exception)
add_subdirectory(3rdparty/boost.winapi)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        Boost::stacktrace
)