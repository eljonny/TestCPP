list (
    APPEND
    TESTCPP_PUBLIC_HEADERS
    include/TestCPP.h
)

list (
    APPEND
    TESTCPP_PRIVATE_HEADERS
    include/internal/TestCPPAssertions.h
    include/internal/TestCPPCommon.h
    include/internal/TestCPPExceptions.h
    include/internal/TestCPPTestCase.h
    include/internal/TestCPPTestSuite.h
    include/internal/TestCPPUtil.h
)

set_target_properties (
    ${PROJECT_NAME}
    PROPERTIES
        PUBLIC_HEADER
        "${TESTCPP_PUBLIC_HEADERS}"
)
set_target_properties (
    ${PROJECT_NAME}
    PROPERTIES
        PRIVATE_HEADER
        "${TESTCPP_PRIVATE_HEADERS}"
)
include (GNUInstallDirs)
install (
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    PUBLIC_HEADER
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    PRIVATE_HEADER
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/internal
)
export (
    EXPORT ${PROJECT_NAME}Targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
)
install (
    EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_GROUP_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
