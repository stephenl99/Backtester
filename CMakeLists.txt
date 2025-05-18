cmake_minimum_required(VERSION 3.29)
project(Backtester)

set(CMAKE_CXX_STANDARD 20)
set (PYBIND11_PYTHON_VERSION "3.12")
include_directories(/Users/stephenlinder/miniconda3/pkgs/python-3.12.8-h99e199e_0/include/python3.12/)
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
        Portfolio.cpp
        ExecutionHandler.h
        ExecutionHandler.cpp
        pythonBindings.h
        pythonBindings.cpp)
