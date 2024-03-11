cmake_minimum_required (VERSION 3.16)

## Use the variable PROJECT_NAME for changing the target name
set (PROJECT_NAME "TestCPP")

## Set our project name
project (${PROJECT_NAME} VERSION 0.1)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library (
    ${PROJECT_NAME}
    src/Test.cpp
)
add_executable (
    ${PROJECT_NAME}_run
    src/main.cpp
)

if (${CMAKE_BUILD_TYPE} EQUAL "Release")
    if (MSVC)
        target_compile_options (${PROJECT_NAME} PUBLIC /W4 /O2)
    else ()
        target_compile_options (${PROJECT_NAME} PUBLIC -O3 -Wall -Wextra -Wpedantic)
    endif ()
else ()
    if (MSVC)
        target_compile_options (${PROJECT_NAME} PUBLIC /W4 /Od)
    else ()
        target_compile_options (${PROJECT_NAME} PUBLIC -g -Og -Wall -Wextra -Wpedantic)
    endif ()
endif ()

target_include_directories (
    ${PROJECT_NAME} PUBLIC
    include
)

target_include_directories (
    ${PROJECT_NAME}_run PUBLIC
    include
)

target_link_libraries (
    ${PROJECT_NAME}_run
    TestCPP
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
    PUBLIC_HEADER
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
