project(HW)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/3rd/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(BASE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/base/include")

set(BASE_SRC_DIR "${PROJECT_SOURCE_DIR}/base/src")

set(GAME_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/game/include")

set(GAME_SRC_DIR "${PROJECT_SOURCE_DIR}/game/src")

set(CLIENT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/client/include")

set(CLIENT_SRC_DIR "${PROJECT_SOURCE_DIR}/client/src")

set(LUA_SRC_DIR "${PROJECT_SOURCE_DIR}/3rd/lua-5.1.4/src")

set(PROTOBUFF_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rd/google/protobuf")

set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/common/include")

set(COMMON_SRC_DIR "${PROJECT_SOURCE_DIR}/common/src")

add_subdirectory("${BASE_SRC_DIR}")

add_subdirectory("${COMMON_SRC_DIR}")

add_subdirectory("${GAME_SRC_DIR}")

add_subdirectory("${CLIENT_SRC_DIR}")