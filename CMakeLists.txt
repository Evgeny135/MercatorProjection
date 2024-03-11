cmake_minimum_required(VERSION 3.27)
project(MercatorProjection)

set(CMAKE_CXX_STANDARD 14)

add_executable(MercatorProjection main.cpp
        Matrix.h
        Bmp.cpp
        Bmp.h
)
