add_library(${AOFC_UTILS_LIB} STATIC
"FileHandler.cpp")

target_include_directories(${AOFC_UTILS_LIB} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)