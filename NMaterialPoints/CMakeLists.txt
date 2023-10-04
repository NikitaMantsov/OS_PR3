cmake_minimum_required(VERSION 3.26)
project(NMaterialPoints C)

set(CMAKE_C_STANDARD 99)

add_executable(NMaterialPoints main.c)
# Link the math library
target_link_libraries(NMaterialPoints m)
