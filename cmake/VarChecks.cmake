if (NOT DEFINED CMAKE_COVERAGE_ENABLED)
    message ("-- Not defined CMAKE_COVERAGE_ENABLED")
    set (CMAKE_COVERAGE_ENABLED 0)

else ()
    message ("-- Defd CMAKE_COVERAGE_ENABLED ${CMAKE_COVERAGE_ENABLED}")
endif ()

if (NOT DEFINED CMAKE_DEMO_ENABLED)
    message ("-- Not defined CMAKE_DEMO_ENABLED")
    set (CMAKE_DEMO_ENABLED 0)

else ()
    message ("-- Defd CMAKE_DEMO_ENABLED ${CMAKE_DEMO_ENABLED}")
endif ()

if (NOT DEFINED CMAKE_TEST_ENABLED)
    message ("-- Not defined CMAKE_TEST_ENABLED")
    set (CMAKE_TEST_ENABLED 0)

else ()
    message ("-- Defd CMAKE_TEST_ENABLED ${CMAKE_TEST_ENABLED}")
endif ()

if (${CMAKE_TEST_ENABLED})
    message ("-- Testing enabled!")
    include (CTest)
endif ()
