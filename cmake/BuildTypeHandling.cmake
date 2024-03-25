if (${CMAKE_BUILD_TYPE} EQUAL "Release")
    message ("-- Release build compilation options enabled")

    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            /W4 /O2
        )
        
        if (${CMAKE_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                /W4 /O2
            )
        endif ()
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                /W4 /O2
            )
            
            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
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
        
        if (${CMAKE_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )
        endif ()
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )
            
            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                -O3 -Wall -Wextra -Wpedantic
            )
        endif ()
    endif ()
    
else ()
    message ("-- Debug build compilation options enabled")
    
    if (MSVC)
        target_compile_options (
            ${PROJECT_NAME}
            PUBLIC
            /W4 /Od
        )
        
        if (${CMAKE_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC
                /W4 /Od
            )
        endif ()
        
        if (BUILD_TESTING)
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                /W4 /Od
            )
            
            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
                PUBLIC
                /W4 /Od
            )
        endif ()
        
    else ()
        if (${CMAKE_DEMO_ENABLED})
            target_compile_options (
                ${PROJECT_NAME}_run
                PUBLIC -g -Og -Wall -Wextra -Wpedantic
            )
        endif ()
        
        if (BUILD_TESTING AND ${CMAKE_COVERAGE_ENABLED})
            message ("-- Coverage compilation options enabled")

            target_compile_options (
                ${PROJECT_NAME}
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )
            
            target_compile_options (
                ${PROJECT_NAME}_TestCase_test
                PUBLIC
                    -g -Og -Wall -Wextra -Wpedantic -fprofile-arcs
                    -ftest-coverage
            )
            
            target_compile_options (
                ${PROJECT_NAME}_TestSuite_test
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
