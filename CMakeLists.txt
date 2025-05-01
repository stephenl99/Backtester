cmake_minimum_required(VERSION 3.29)
project(Backtester)

set(CMAKE_CXX_STANDARD 14)

add_executable(Backtester
    ATR.cpp
    Data.cpp
    Main.cpp
        Event.cpp)
