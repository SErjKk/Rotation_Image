cmake_minimum_required(VERSION 3.23)
project(123 C)

set(CMAKE_C_STANDARD 11)

add_executable(RotationLab_1 src/main.c src/image.c src/rotate.c src/files.c descriptions/image.h descriptions/files.h descriptions/rotate.h)

