#project(base)

include_directories("${BASE_INCLUDE_DIR}")

include_directories("${PROTOBUFF_INCLUDE_DIR}")

aux_source_directory("${BASE_SRC_DIR}" BASE_SRC)

aux_source_directory("${LUA_SRC_DIR}" LUA_SRC)

add_library(base STATIC "${LUA_SRC}" "${BASE_SRC}")