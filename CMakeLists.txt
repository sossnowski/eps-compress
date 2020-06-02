cmake_minimum_required(VERSION 3.15)
project(epsCompress)


set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp Compress.cpp Compress.h File.cpp File.h Coords.h)

add_subdirectory(Boost_tests)


