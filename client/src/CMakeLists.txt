include_directories("${BASE_INCLUDE_DIR}")

include_directories("${PROTOBUFF_INCLUDE_DIR}")

include_directories("${COMMON_INCLUDE_DIR}")

add_executable(client main.cpp)

add_executable(multiclient multimain.cpp)

find_package(Threads)

target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(client ${LIBRARY_OUTPUT_PATH}/libbase.a)

target_link_libraries(client ${LIBRARY_OUTPUT_PATH}/libcommon.a)

target_link_libraries(client ${LIBRARY_OUTPUT_PATH}/libprotobuf.a)

target_link_libraries(multiclient ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(multiclient ${LIBRARY_OUTPUT_PATH}/libbase.a)

target_link_libraries(multiclient ${LIBRARY_OUTPUT_PATH}/libprotobuf.a)