cmake_minimum_required(VERSION 3.24)
project(rk2_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(rk2_1 main.c lines.c lines.h cJSON.c cJSON.h)
