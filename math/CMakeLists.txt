project(maths)
cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)

message(CHECK_START "Fetching Eigen3")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

include(FetchContent)
FetchContent_Declare(
  Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  # GIT_TAG master
  GIT_TAG 3.4.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)

# note: To disable eigen tests,
# you should put this code in a add_subdirectory to avoid to change
# BUILD_TESTING for your own project too since variables are directory
# scoped
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_MPL2_ONLY ON)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_BUILD_DOC OFF)
FetchContent_MakeAvailable(Eigen)

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

# FetchContent_Declare(
#   glm
#   GIT_REPOSITORY https://github.com/g-truc/glm.git
#   # try bleeding edge..
#   GIT_TAG 5d73e17e58a7ddb0c6c5ce7a4783a2c60df804d0
#   # GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
# )

# FetchContent_MakeAvailable(glm)

# NOTE: installed matplotplusplus from AUR
find_package(Matplot++ REQUIRED)

set(
  SOURCES
  src/creppl.cpp
  # src/dft.cpp
)

# add_executable(main src/main.cpp ${SOURCES})
# target_link_libraries(main SDL2::Main SDL2::Image SDL2::Mixer SDL2::TTF)

add_executable(maths src/main.cpp ${SOURCES})
target_link_libraries(maths PRIVATE Eigen3::Eigen)
target_link_libraries(maths PRIVATE Matplot++::matplot)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_CXX_thing is ${CMAKE_CXX_STANDARD_REQUIRED}")

message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

# cmake -H. -B_builds -DCMAKE_CONFIGURATION_TYPES="Debug;MyRelease" -DCMAKE_CXX_FLAGS_MYRELEASE="/My-Rel-flag" -DCMAKE_EXE_LINKER_FLAGS_MYRELEASE="/My-Linker-flags" "-GVisual Studio 12 2013 Win64"
