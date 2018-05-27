#project(base)

include_directories("${BASE_INCLUDE_DIR}")

include_directories("${PROTOBUFF_INCLUDE_DIR}")

aux_source_directory("${BASE_SRC_DIR}" BASE_SRC)

add_library(base STATIC "${BASE_SRC}")