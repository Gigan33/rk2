cmake_minimum_required(VERSION 3.24)
project(rk_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(rk_2 main.c lines.c lines.h cJSON.c cJSON.h)
