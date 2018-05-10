include_directories("${BASE_INCLUDE_DIR}")

add_executable(client main.cpp)

find_package(Threads)

target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(client ${PROJECT_SOURCE_DIR}/lib/libbase.a)