project(hamming)

add_library(${PROJECT_NAME} STATIC hamming.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
