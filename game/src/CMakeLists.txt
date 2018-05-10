include_directories("${BASE_INCLUDE_DIR}")

add_executable(game1 main.cpp)

find_package(Threads)

target_link_libraries(game1 ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(game1 ${PROJECT_SOURCE_DIR}/lib/libbase.a)