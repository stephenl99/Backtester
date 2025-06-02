cmake_minimum_required(VERSION 3.29)
project(Backtester)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES arm64)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

message(STATUS "Using Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Using Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "Using Python3_LIBRARIES: ${Python3_LIBRARIES}")

# Include Python directories
include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})

# First create a library with all the backtester code
add_library(BacktesterLib STATIC
        Main.cpp
        Data.cpp
        Event.cpp
        DataHandler.cpp
        Strategy.cpp
        Day.cpp
        Global.cpp
        Portfolio.cpp
        ExecutionHandler.cpp)

# Create the Python binding module and link it with BacktesterLib
pybind11_add_module(PythonBinding PythonBinding.cpp)
target_link_libraries(PythonBinding PRIVATE BacktesterLib)

# Create the main executable and link it with BacktesterLib
add_executable(Backtester Main.cpp
        Utilities.h
        Utilities.cpp)
target_link_libraries(Backtester PRIVATE BacktesterLib ${Python3_LIBRARIES})

#include_directories(/opt/homebrew/opt/python@3.13/Frameworks/Python.framework/Versions/3.13/include/python3.13/)
#include_directories(/Users/stephenlinder/miniconda3/pkgs/python-3.12.8-h99e199e_0/include/python3.12/)
