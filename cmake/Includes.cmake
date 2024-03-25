target_include_directories (
    ${PROJECT_NAME} PRIVATE
    include
)

if (${CMAKE_DEMO_ENABLED})
    target_include_directories (
        ${PROJECT_NAME}_run PRIVATE
        demo/include
        include
    )
endif ()

if (BUILD_TESTING)
    target_include_directories (
        ${PROJECT_NAME}_TestCase_test PRIVATE
        test/include
        include
    )
    
    target_include_directories (
        ${PROJECT_NAME}_TestSuite_test PRIVATE
        test/include
        include
    )
endif ()
