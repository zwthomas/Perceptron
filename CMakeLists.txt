cmake_minimum_required(VERSION 3.8)
project(Perceptron)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Perceptron.cpp
        Perceptron.h
        Network.cpp
        Network.h
        )
add_executable(Perceptron ${SOURCE_FILES})