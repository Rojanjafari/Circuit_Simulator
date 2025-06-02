cmake_minimum_required(VERSION 3.30)
project(Circuit_Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(CircuitSimulator
        main.cpp
        src/CircuitElement.cpp
        src/Resistor.cpp
        src/Capacitor.cpp
        src/Inductor.cpp
        src/Ground.cpp
        src/Circuit.cpp
)