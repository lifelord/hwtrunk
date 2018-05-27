include_directories("${BASE_INCLUDE_DIR}")

add_executable(game main.cpp)

find_package(Threads)

target_link_libraries(game ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(game ${LIBRARY_OUTPUT_PATH}/libbase.a)

target_link_libraries(game ${LIBRARY_OUTPUT_PATH}/liblua.a)

target_link_libraries(game ${LIBRARY_OUTPUT_PATH}/libprotobuf.a)