list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/link")

if (${TESTCPP_DEMO_ENABLED})
    include (Demo)
endif ()

if (BUILD_TESTING)
    if (${TESTCPP_COVERAGE_ENABLED})
        message (STATUS "Linking in gcov")

        include (TestCPPWithCoverage)
        include (TestsWithCoverage)

    else ()
        include (Tests)
    endif ()
endif ()
