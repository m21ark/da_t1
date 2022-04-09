cmake_minimum_required(VERSION 3.10)
project(da_t1)

set(CMAKE_CXX_STANDARD 11)

set(CREATE_EXE TRUE)





    add_executable(da_t1 main.cpp

            src/read_files.cpp include/read_files.h

            src/knapsack.cpp include/knapsack.h)

    message("Release mode")


