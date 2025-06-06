set (
    CPACK_SOURCE_IGNORE_FILES
        "build-debug" "build-release" ".clang"
        ".codelite" ".git" "_packages" "test_package/build"
)

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY
        "Simple C++ programmatic testing library."
    CACHE STRING "Package description for the package metadata"
)
set (CPACK_PACKAGE_VENDOR "eljonny")

set (CPACK_VERBATIM_VARIABLES YES)

# This ensures that the zip package is created with the same structure
#  as the tar.gz and other binary packages.
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

set (CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set (CPACK_OUTPUT_FILE_PREFIX
        "${CMAKE_SOURCE_DIR}/_packages/${CMAKE_BUILD_TYPE}")

set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set (CPACK_PACKAGE_CONTACT "jonathan@hyrysoftwarefoundation.org")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER
        "Jonathan Hyry <${CPACK_PACKAGE_CONTACT}>")
set (CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/eljonny/TestCPP")

set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set (CPACK_DEBIAN_PACKAGE_DEPENDS libstdc++6)

set (
    CPACK_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

set (CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set (CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set (CPACK_DEB_COMPONENT_INSTALL YES)

set (CPACK_WIX_UPGRADE_GUID "EDB6D016-633E-4A35-AD5A-7734F6F3E6A5")
set (CPACK_WIX_LICENSE_RTF "${CMAKE_CURRENT_SOURCE_DIR}/res/license/wix/LICENSE.rtf")
set (CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}/res/img/testcpp.ico")
set (CPACK_WIX_UI_BANNER "${CMAKE_CURRENT_SOURCE_DIR}/res/img/wix/testcpp-inst-banner.bmp")
set (CPACK_WIX_UI_DIALOG "${CMAKE_CURRENT_SOURCE_DIR}/res/img/wix/testcpp-inst-dialog.bmp")
set (CPACK_WIX_CMAKE_PACKAGE_REGISTRY "${PROJECT_NAME}")

include (CPack)

include (CMakePackageConfigHelpers)
configure_package_config_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
