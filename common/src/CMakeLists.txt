#project(common)

include_directories("${PROTOBUFF_INCLUDE_DIR}")

include_directories("${COMMON_INCLUDE_DIR}")

aux_source_directory("${COMMON_SRC_DIR}" COMMON_SRC)

add_library(common STATIC "${COMMON_SRC}")