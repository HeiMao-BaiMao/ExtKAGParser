cmake_minimum_required(VERSION 3.16)

project(ExtKAGParser LANGUAGES CXX)

# UTF-8 support for MSVC
if(MSVC)
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:C>:/utf-8>"
    "$<$<COMPILE_LANGUAGE:CXX>:/utf-8>"
    "$<$<COMPILE_LANGUAGE:CXX>:/Zc:__cplusplus>"
  )
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define the source and header files
set(SOURCES
  src/KAGParser.cpp
  src/Main.cpp
  src/TJSAry.cpp
  src/TJSDic.cpp
  src/tp_stub.cpp
)

set(HEADERS
  src/TJSAry.h
  src/TJSDic.h
  src/ExtKAGParser.h
  src/KAGParser.h
  src/tjsHashSearch.h
  src/tp_stub.h
)

set(RESOURCES
  src/KAGParser.rc
)

# Create shared library
add_library(ExtKAGParser SHARED
  ${SOURCES}
  ${HEADERS}
  ${RESOURCES}
)

# Preprocessor definitions
target_compile_definitions(ExtKAGParser PRIVATE
  WIN32
  _WINDOWS
  _USRDLL
  EXTKAGPARSER_EXPORTS
  $<$<CONFIG:Debug>:_DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
)

# Use /MT instead of /MD for MSVC
if(MSVC)
  foreach(flag_var
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_RELEASE)
    string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
  endforeach()

  target_compile_options(ExtKAGParser PRIVATE /W3)
endif()