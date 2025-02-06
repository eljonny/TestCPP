list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/build")

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE ${CMAKE_CONFIGURATION_TYPES})
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message (STATUS "Release build compilation options enabled")

    if (MSVC AND NOT ("${CMAKE_VS_PLATFORM_TOOLSET}" STREQUAL "ClangCL"))
        message (STATUS "MSVC Release build compilation options enabled")

        include (MSVCRelease)

    else ()
        message (STATUS "GCC/Clang Release build compilation options enabled")

        include (GCCClangRelease)
    endif ()

else ()
    message (STATUS "Debug build compilation options enabled")

    include (DebugCompileDefs)
    
    if (MSVC AND NOT ("${CMAKE_VS_PLATFORM_TOOLSET}" STREQUAL "ClangCL"))
        message (STATUS "MSVC Debug build compilation options enabled")

        include (MSVCDebug)

    else ()
        message (STATUS "GCC/Clang Debug build compilation options enabled")

        include (GCCClangDebug)
    endif ()
endif ()

include (CompileDefs)
