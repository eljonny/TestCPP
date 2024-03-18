add_library (
    ${PROJECT_NAME}
    src/Test.cpp
)
add_library (
    ${PROJECT_GROUP_NAME}::${PROJECT_NAME}
    ALIAS
        ${PROJECT_NAME}
)

if (${CMAKE_DEMO_ENABLED})
    add_executable (
        ${PROJECT_NAME}_run
        src/main.cpp
    )
endif ()

if (BUILD_TESTING)
    add_executable (
        ${PROJECT_NAME}_test
        test/src/TestCPPTestMain.cpp
    )
endif ()
