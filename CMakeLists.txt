cmake_minimum_required(VERSION 3.0.0)
project(aofc2k22 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(AOFC_UTILS_LIB "library")

add_subdirectory(utils)

set(DAYS Day1 Day2 Day3 Day4)

foreach(DAY ${DAYS})
    add_subdirectory(${DAY})
    file(COPY ${DAY}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${DAY})
endforeach()
