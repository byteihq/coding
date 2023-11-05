
include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        10.1.1
)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG        v1.12.0
)
FetchContent_MakeAvailable(fmt spdlog)

add_subdirectory(third_party)
add_subdirectory(utils)
add_subdirectory(common)
add_subdirectory(code)
add_subdirectory(hamming)

target_link_libraries(code PUBLIC Eigen3::Eigen common)
target_link_libraries(utils PUBLIC code common fmt::fmt-header-only)
target_link_libraries(common PRIVATE utils)
target_link_libraries(hamming PUBLIC code common utils)
