if (${CMAKE_DEMO_ENABLED})
    target_link_libraries (
        ${PROJECT_NAME}_run
        ${PROJECT_NAME}
    )
endif ()

if (BUILD_TESTING)
    if (${CMAKE_COVERAGE_ENABLED})
        message ("-- Linking in gcov")

        target_link_libraries (
            ${PROJECT_NAME}
            gcov
        )
        target_link_libraries (
            ${PROJECT_NAME}_test
            ${PROJECT_NAME}
            gcov
        )
    
    else ()
        target_link_libraries (
            ${PROJECT_NAME}_test
            ${PROJECT_NAME}
        )
    
    endif ()
endif ()
