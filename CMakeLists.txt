cmake_minimum_required (VERSION 3.16)

set (PROJECT_NAME "TestCPP")
set (PROJECT_GROUP_NAME "cpptesting")

project (${PROJECT_NAME} VERSION 0.2.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

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
