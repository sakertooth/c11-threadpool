cmake_minimum_required(VERSION 3.0.0)
project(helloworld VERSION 0.1.0 LANGUAGES C)

add_executable(helloworld helloworld.c)
target_include_directories(helloworld PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(queue queue.c)
target_include_directories(queue PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(UNIX)
    target_link_libraries(helloworld pthread)
    target_link_libraries(queue pthread)
endif()

