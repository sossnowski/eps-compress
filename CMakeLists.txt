cmake_minimum_required(VERSION 3.15)
project(epsCompress)

set(CMAKE_CXX_STANDARD 14)



add_executable(epsCompress main.cpp Compress.cpp Compress.h File.cpp File.h Coords.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(epsCompress ${SFML_LIBRARIES})
endif()