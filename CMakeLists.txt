cmake_minimum_required(VERSION 3.0.0)
project(aofc2k22 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


set(DAY1_EXE "day1")
set(DAY2_EXE "day2")

set(AOFC_UTILS_LIB "library")

add_subdirectory(utils)

add_subdirectory(Day1)
file(COPY Day1/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Day1)

add_subdirectory(Day2)
file(COPY Day2/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Day2)
