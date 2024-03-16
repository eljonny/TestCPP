cmake_minimum_required (VERSION 3.16)

set (PROJECT_NAME "TestCPP")
set (PROJECT_GROUP_NAME "cpptesting")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project (${PROJECT_NAME} VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_TEST_ENABLED})
    include (CTest)
endif ()

add_library (
    ${PROJECT_NAME}
    src/Test.cpp
)
add_library (
    ${PROJECT_GROUP_NAME}::${PROJECT_NAME}
    ALIAS
        ${PROJECT_NAME}
)
add_executable (
    ${PROJECT_NAME}_run
    src/main.cpp
)

if (BUILD_TESTING)
    add_executable (
        ${PROJECT_NAME}_test
        test/src/TestCPPTestMain.cpp
    )
endif ()

if (${CMAKE_BUILD_TYPE} EQUAL "Release")
    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            /W4 /O2
        )
        target_compile_options (
            ${PROJECT_NAME}_run
            PUBLIC
            /W4 /O2
        )
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_test
                PUBLIC
                /W4 /O2
            )
        endif ()
        
    else ()
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            -O3 -Wall -Wextra -Wpedantic
        )
        target_compile_options (
            ${PROJECT_NAME}_run
            PUBLIC
            -O3 -Wall -Wextra -Wpedantic
        )
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_test
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )
        endif ()
    endif ()
    
else ()
    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            /W4 /Od
        )
        target_compile_options (
            ${PROJECT_NAME}_run
            PUBLIC
            /W4 /Od
        )
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_test
                PUBLIC
                /W4 /Od
            )
        endif ()
        
    else ()
        target_compile_options (
            ${PROJECT_NAME}_run
            PUBLIC -g -Og -Wall -Wextra -Wpedantic
        )
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )
            target_compile_options (
                ${PROJECT_NAME}_test
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )
        
        else ()
            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC -g -Og -Wall -Wextra -Wpedantic
            )
        endif ()
    endif ()
endif ()

target_include_directories (
    ${PROJECT_NAME} PRIVATE
    include
)
target_include_directories (
    ${PROJECT_NAME}_run PRIVATE
    include
)

if (BUILD_TESTING)
    target_include_directories (
        ${PROJECT_NAME}_test PRIVATE
        test/include
        include
    )
endif ()

target_link_libraries (
    ${PROJECT_NAME}_run
    ${PROJECT_NAME}
)

if (BUILD_TESTING)
    target_link_libraries (
        ${PROJECT_NAME}
        gcov
    )
    target_link_libraries (
        ${PROJECT_NAME}_test
        ${PROJECT_NAME}
        gcov
    )
    
    add_test (
        NAME ${PROJECT_NAME}Tests
        COMMAND ${PROJECT_NAME}_test
    )
endif ()

include (CMakePackageConfigHelpers)
configure_package_config_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

set_target_properties (
    ${PROJECT_NAME}
    PROPERTIES
        PUBLIC_HEADER
        include/Test.h
)
include (GNUInstallDirs)
install (
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    PUBLIC_HEADER
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
export (
    EXPORT ${PROJECT_NAME}Targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
)
install (
    EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_GROUP_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include (Packing)
