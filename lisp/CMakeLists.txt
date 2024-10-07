# mkdir build;cd build; cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..;ninja;
cmake_minimum_required(VERSION 3.14.0)
project(lisp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  # TODO: this coincidentally has same tag as eigen? Sus.
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

set(
  SOURCES
  src/scanner.cpp
  src/token.cpp
)

set(
  TEST_SOURCES
  src/scanner.cpp
  src/token.cpp
)

set(LIBS "-lreadline")
add_executable(lisp "src/main.cpp" ${SOURCES})
target_include_directories(lisp PRIVATE "src/")
target_link_libraries(lisp readline)

add_executable(tests src/test.cpp ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
