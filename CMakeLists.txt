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
find_package(yaml-cpp REQUIRED)
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
    Main.cpp
    AnalyzerApp.cpp
    AnalyzersFactory.cpp
    Analyzers/CppCheck.cpp
    Analyzers/ClangTidy.cpp)
#-------------------------------------------------------------------------------
# target
add_executable(xAnalyzer ${SOURCES})
#-------------------------------------------------------------------------------
# flags
if     (MSVC)
    set(FLAGS "/W3")
elseif (MINGW)
    set(FLAGS "-Wall -pipe")
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(FLAGS "-pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow -Wno-unused-parameter "
        "-Wno-unused-variable -Wno-unknown-pragmas -Wno-return-type-c-linkage -Werror "
        "-fcolor-diagnostics -Qunused-arguments -U__STRICT_ANSI__ -D__STDC_FORMAT_MACROS")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(FLAGS "-pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow -Wno-unused-parameter "
        "-Wno-unused-variable -Wno-unknown-pragmas -Wno-return-type-c-linkage -Werror "
        "-U__STRICT_ANSI__ -D__STDC_FORMAT_MACROS")
else()
    message("xLib: unknown compiler")
endif()

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        # COMPILE_DEFINITIONS
        COMPILE_FLAGS ${FLAGS})

target_link_libraries(
    ${PROJECT_NAME}
    ${XLIB_LIBRARIES}
    ${YAML_CPP_LIBRARIES})
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${CMAKE_SOURCE_DIR}/Config.h.in
    ${CMAKE_SOURCE_DIR}/Config.h)
#--------------------------------------------------------------------------------------------------
