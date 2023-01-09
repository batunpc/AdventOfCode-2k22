cmake_minimum_required(VERSION 3.0.0)
project(aofc2k22 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(AOFC_UTILS_LIB "library")

# AoC Days
# --------------
set(DAYS)
foreach(i RANGE 1 5)
    list(APPEND DAYS Day${i})
endforeach()

# Helper Library
# ----------------
add_subdirectory(utils)

# For each day, create an executable and copy the input file
# ----------------------------------------------------------
foreach(DAY ${DAYS}) 
    # Convert to lowercase so I don't have to capslock the executable
    string(TOLOWER ${DAY} LOWERCASE_DAY)
    add_executable(${LOWERCASE_DAY} "${DAY}/main.cpp")
    
    set_target_properties(${LOWERCASE_DAY} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${DAY}
    )
    target_link_libraries(${LOWERCASE_DAY} PUBLIC ${AOFC_UTILS_LIB})

    file(COPY ${DAY}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${DAY})
endforeach()
