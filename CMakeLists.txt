cmake_minimum_required(VERSION 3.31)
project(colosseo C)

set(CMAKE_C_STANDARD 11)

add_library(colosseo STATIC colosseo.c)
add_executable(colosseo_main tests/main.c)
target_link_libraries(colosseo_main PRIVATE colosseo)
