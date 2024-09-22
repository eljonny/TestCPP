if (${TESTCPP_STACKTRACE_ENABLED} AND MSVC)
    target_link_libraries (
        ${PROJECT_NAME}_run
        ${PROJECT_NAME}
        ole32
        dbgeng
    )

elseif (${TESTCPP_STACKTRACE_ENABLED})
    target_link_libraries (
        ${PROJECT_NAME}_run
        ${PROJECT_NAME}
        dl
    )

else ()
    target_link_libraries (
        ${PROJECT_NAME}_run
        ${PROJECT_NAME}
    )
endif ()
