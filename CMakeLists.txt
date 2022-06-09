cmake_minimum_required(VERSION 3.10)

project(operators)

add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
find_package(benchmark REQUIRED)
FIND_PACKAGE(OpenMP REQUIRED)

include_directories(include)

add_executable(test_ops src/main.cc src/convert_data_structure.cc src/mini_mat.cc src/allocator.cc src/vision_pre_post_ops.cc)

target_link_libraries(test_ops ${OpenCV_LIBS})
target_link_libraries(test_ops benchmark::benchmark)
target_link_libraries(test_ops OpenMP::OpenMP_CXX)
