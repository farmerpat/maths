project(pfs)
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
# set(BUILD_TESTING OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_MPL2_ONLY ON)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_BUILD_DOC OFF)
FetchContent_MakeAvailable(Eigen)

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  # TODO: this coincidentally has same tag as eigen? Sus.
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

# TODO: probalby just gank/use eigen's FindGMP.cmake
# which is where this came from egein's
if (GMP_INCLUDES AND GMP_LIBRARIES)
  set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDES AND GMP_LIBRARIES)

find_path(GMP_INCLUDES
  NAMES
  gmp.h
  PATHS
  $ENV{GMPDIR}
  ${INCLUDE_INSTALL_DIR}
)

find_library(GMP_LIBRARIES gmp PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG
                                  GMP_INCLUDES GMP_LIBRARIES)
mark_as_advanced(GMP_INCLUDES GMP_LIBRARIES)

set(
  SRCS
  # src/main.cpp
  # src/int_util.cpp
  # src/date_util.cpp
)

set(
  TEST_SRCS
  # src/int_util.cpp
  # src/date_util.cpp
)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

add_executable(pfs src/main.cpp ${SRCS})
# target_include_directories(pfs PRIVATE "${eigen_SOURCE_DIR}/Eigen/src")
target_include_directories(pfs PRIVATE "${GMP_INCLUDES}")
target_include_directories(pfs PRIVATE "${eigen_SOURCE_DIR}")

# message("Eigen_SOURCE_DIR is ${eigen_SOURCE_DIR}/Eigen/src")
target_link_libraries(pfs PRIVATE "${GMP_LIBRARIES}")
target_link_libraries(pfs PRIVATE Eigen3::Eigen)

add_executable(tests src/test.cpp ${TEST_SRCS})
target_include_directories(tests PRIVATE "${GMP_INCLUDES}")
target_link_libraries(tests PRIVATE "${GMP_LIBRARIES}")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)


# message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
# message("CMAKE_CXX_thing is ${CMAKE_CXX_STANDARD_REQUIRED}")
# message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

# cmake -H. -B_builds -DCMAKE_CONFIGURATION_TYPES="Debug;MyRelease" -DCMAKE_CXX_FLAGS_MYRELEASE="/My-Rel-flag" -DCMAKE_EXE_LINKER_FLAGS_MYRELEASE="/My-Linker-flags" "-GNinja"
