cmake_minimum_required (VERSION 3.16)

set (PROJECT_NAME "TestCPP")
set (PROJECT_GROUP_NAME "cpptesting")

project (${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include (VarChecks)

include (Targets)

include (Analyzing)

include (BuildTypeHandling)

include (Includes)

include (Linking)

include (Testing)

include (Installing)

include (Packing)
