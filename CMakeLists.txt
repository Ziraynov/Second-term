cmake_minimum_required(VERSION 3.23)
project(Secondterm C)

set(CMAKE_C_STANDARD 99)

add_executable(Secondterm1 src/lab1/main.c src/lab1/Header.h src/lab1/functions.c)
add_executable(Secondterm2 src/Lab2/Mainlab2.c src/Lab2/Mainlab2.h)
add_executable(Secondterm22 src/Lab2/secondpart/file.c src/Lab2/secondpart/file.h)
add_executable(Secondterm3 src/Lab3/Mainlab3.c src/Lab3/Mainlab3.h src/Lab3/Functionslab3.c)
add_executable(Secondterm4 src/Lab4/Mainlab4.c src/Lab4/Mainlab4.h src/Lab4/Functionslab4.c)
add_executable(Secondterm5 src/Lab5/Mainlab5.c src/Lab5/Mainlab5.h src/Lab5/Functionslab5.c)
