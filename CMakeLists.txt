cmake_minimum_required(VERSION 3.23)
project(Secondterm C)

set(CMAKE_C_STANDARD 99)

add_executable(Secondterm1l src/lab1/main.c src/lab1/Header.h src/lab1/functions.c src/Lab5/Main.c)
add_executable(Secondterm2l src/Lab2/Main.c src/Lab2/Main.h src/Lab2/Functions.c)
add_executable(Secondterm2la src/Lab2/secondpart/file.c src/Lab2/secondpart/file.h)
add_executable(Secondterm3l src/Lab3/Main.c src/Lab3/Main.h src/Lab3/Functions.c)
add_executable(Secondterm4l src/Lab4/Main.c src/Lab4/Main.h src/Lab4/Functions.c)
add_executable(Secondterm5l src/Lab5/Main.c src/Lab5/Main.h src/Lab5/Functions.c)