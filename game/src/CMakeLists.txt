include_directories("${BASE_INCLUDE_DIR}")

add_executable(game main.cpp)

find_package(Threads)

target_link_libraries(game ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(game ${PROJECT_SOURCE_DIR}/lib/libbase.a)