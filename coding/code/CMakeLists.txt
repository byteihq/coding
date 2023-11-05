project(code)

add_library(${PROJECT_NAME} STATIC code_info.cpp test_matrix.cpp msg_info.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
