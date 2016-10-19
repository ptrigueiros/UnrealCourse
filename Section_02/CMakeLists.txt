cmake_minimum_required(VERSION 3.6)
project(BullCowGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FBullCowGame.h FBullCowGame.cpp)
add_executable(BullCowGame ${SOURCE_FILES})