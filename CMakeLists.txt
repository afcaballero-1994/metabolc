cmake_minimum_required(VERSION 3.27)
project(metabolc C)

set(CMAKE_C_STANDARD 23)

add_executable(metabolc src/main.c
        src/mathV.h)
target_link_libraries(metabolc PRIVATE SDL2 m)
