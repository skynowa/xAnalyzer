#-------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief
#-------------------------------------------------------------------------------


cmake_minimum_required (VERSION 2.6)


project(xAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#--------------------------------------------------------------------------------------------------
# find packages
list(APPEND CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules/CMakeLib")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

find_package(xLib     REQUIRED)
find_package(LibXml2  REQUIRED)

# yaml-cpp
## find_package(yaml-cpp REQUIRED)
# message(STATUS "yaml-cpp_CONFIG:      ${yaml-cpp_CONFIG}")
# message(STATUS "YAML_CPP_INCLUDE_DIR: ${YAML_CPP_INCLUDE_DIR}")
# message(STATUS "YAML_CPP_LIBRARIES:   ${YAML_CPP_LIBRARIES}")
#-------------------------------------------------------------------------------
# includes
include_directories(
    ${LIBXML2_INCLUDE_DIR}
    ${YAML_CPP_INCLUDE_DIR})
#-------------------------------------------------------------------------------
# sources
set(SOURCES
    AnalyzerApp.cpp
    AnalyzersFactory.cpp
    Log.cpp
    Analyzers/AnalyzerDataIn.cpp
    Analyzers/AnalyzerDataOut.cpp
    Analyzers/IAnalyzer.cpp
    Analyzers/CppCheck.cpp
    Analyzers/ClangTidy.cpp)
#-------------------------------------------------------------------------------
# target
add_executable(xAnalyzer ${SOURCES})
#-------------------------------------------------------------------------------
# flags
include(CxxFlags)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        # COMPILE_DEFINITIONS
        COMPILE_FLAGS ${CMAKE_CXX_FLAGS})

target_link_libraries(
    ${PROJECT_NAME}
    ${cmXLIB_LIBRARIES}
    ${YAML_CPP_LIBRARIES})
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${CMAKE_SOURCE_DIR}/Config.h.in
    ${CMAKE_SOURCE_DIR}/Config.h)
#--------------------------------------------------------------------------------------------------
