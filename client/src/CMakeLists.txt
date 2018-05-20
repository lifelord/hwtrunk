include_directories("${BASE_INCLUDE_DIR}")

add_executable(client main.cpp)

add_executable(multiclient multimain.cpp)

find_package(Threads)

target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(client ${PROJECT_SOURCE_DIR}/lib/libbase.a)

target_link_libraries(multiclient ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(multiclient ${PROJECT_SOURCE_DIR}/lib/libbase.a)