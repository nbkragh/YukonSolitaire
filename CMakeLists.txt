cmake_minimum_required(VERSION 3.17)
project(YukonSolitaire C)

set(CMAKE_C_STANDARD 11)

add_executable(YukonSolitaire
        main.c
        CardLoad.c
        CardFunctions.h)
