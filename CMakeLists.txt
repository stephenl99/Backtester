cmake_minimum_required(VERSION 3.29)
project(Backtester)

set(CMAKE_CXX_STANDARD 20)

add_executable(Backtester
        Main.cpp
        Data.cpp
        Event.cpp
        Event.h
        DataHandler.h
        Main.h
        DataHandler.cpp
        Data.h
        Day.h
        Strategy.h
        Strategy.cpp
        Day.cpp
        Global.h
        Global.cpp
        Portfolio.h
        Portfolio.cpp)
