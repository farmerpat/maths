# mkdir build;cd build; cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..;ninja;
project(dice)
cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set (CMAKE_CXX_STANDARD 20)
# I think it isn't quite ready yet...
set (CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  # TODO: this coincidentally has same tag as eigen? Sus.
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

set(
  SRCS
  # src/main.cpp
)

set(
  TEST_SRCS
  # src/int_util.cpp
)

add_executable(dice src/main.cpp ${SRCS})

add_executable(tests src/test.cpp ${TEST_SRCS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
