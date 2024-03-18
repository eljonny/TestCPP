target_include_directories (
    ${PROJECT_NAME} PRIVATE
    include
)

if (${CMAKE_DEMO_ENABLED})
    target_include_directories (
        ${PROJECT_NAME}_run PRIVATE
        include
    )
endif ()

if (BUILD_TESTING)
    target_include_directories (
        ${PROJECT_NAME}_test PRIVATE
        test/include
        include
    )
endif ()
