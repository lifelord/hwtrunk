#project(base)

include_directories("${BASE_INCLUDE_DIR}") 

aux_source_directory("${PROJECT_SOURCE_DIR}/base/src" BASE_SRC)

add_library(base STATIC "${BASE_SRC}")