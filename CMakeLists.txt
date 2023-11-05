cmake_minimum_required(VERSION 3.19)

project(coding)

add_executable(${PROJECT_NAME}_bin main.cpp)

add_subdirectory(coding)
target_link_libraries(${PROJECT_NAME}_bin PRIVATE hamming)
