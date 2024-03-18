if (BUILD_TESTING)
    add_test (
        NAME ${PROJECT_NAME}Tests
        COMMAND ${PROJECT_NAME}_test
    )
endif ()
