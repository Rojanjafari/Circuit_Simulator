cmake_minimum_required(VERSION 3.30)
project(Circuit_Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Circuit_Simulator
        main.cpp
        CircuitElement.cpp
        Resistor.cpp
        Capacitor.cpp
        Inductor.cpp
        Ground.cpp
        Circuit.cpp
)