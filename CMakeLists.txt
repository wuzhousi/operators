cmake_minimum_required(VERSION 3.10)

project(operators)

find_package(OpenCV REQUIRED)
find_package(benchmark REQUIRED)

add_subdirectory(pre_post_ops)

add_executable(test_ops main.cc)

target_link_libraries(test_ops ${OpenCV_LIBS})
target_link_libraries(test_ops benchmark::benchmark)
target_link_libraries(test_ops pre_post_ops)
