cmake_minimum_required(VERSION 3.0.0)
project(aofc2k22 VERSION 0.1.0)

set(DAY1_EXE "day1")
set(AOFC_UTILS_LIB "library")

add_subdirectory(utils)

add_subdirectory(Day1)
file(COPY Day1/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Day1)

