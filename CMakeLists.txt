cmake_minimum_required(VERSION 3.0.0)
project(c11-threadpool VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_library(c11-threadpool INTERFACE)
target_include_directories(c11-threadpool INTERFACE "include")

add_subdirectory(tests)
add_test(NAME helloworld COMMAND helloworld)
add_test(NAME queue COMMAND queue)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
