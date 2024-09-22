list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/build")

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE ${CMAKE_CONFIGURATION_TYPES})
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message (STATUS "Release build compilation options enabled")

    if (MSVC)
        include (MSVCRelease)

    else ()
        include (GCCClangRelease)
    endif ()

else ()
    message (STATUS "Debug build compilation options enabled")

    include (DebugCompileDefs)

    if (MSVC)
        include (MSVCDebug)

    else ()
        include (GCCClangDebug)
    endif ()
endif ()

include (CompileDefs)
