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

# Create the Python binding module
pybind11_add_module(PythonBinding PythonBinding.cpp)

# Create the main executable (without PythonBinding.cpp)
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
        ExecutionHandler.cpp)

target_link_libraries(Backtester PRIVATE ${Python3_LIBRARIES})

#include_directories(/opt/homebrew/opt/python@3.13/Frameworks/Python.framework/Versions/3.13/include/python3.13/)
#include_directories(/Users/stephenlinder/miniconda3/pkgs/python-3.12.8-h99e199e_0/include/python3.12/)
