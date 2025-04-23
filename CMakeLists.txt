cmake_minimum_required(VERSION 3.16)

# UTF-8 source
add_compile_options("$<$<AND:$<C_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:C>>:/utf-8>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/utf-8>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/Zc:__cplusplus>")

# MSVC static runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(PROJECT_NAME ExtKAGParser)
set(PROJECT_VERSION 1.00)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# tp_stub をサブディレクトリとして追加
if(NOT TARGET tp_stub)
    add_subdirectory(../tp_stub ${CMAKE_CURRENT_BINARY_DIR}/tp_stub)
endif()

# ソースファイル
add_library(${PROJECT_NAME} SHARED
    src/KAGParser.cpp
    src/Main.cpp
    src/TJSAry.cpp
    src/TJSDic.cpp
    src/KAGParser.rc
)

# インクルードディレクトリ（必要なら追加）
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 定義
target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32
    _WINDOWS
    _USRDLL
    EXTKAGPARSER_EXPORTS
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# ライブラリリンク
target_link_libraries(${PROJECT_NAME} PUBLIC
    tp_stub
)