cmake_minimum_required(VERSION 3.30)
project(Circuit_simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Circuit_simulator
        main.cpp
        CircuitElement.cpp
        Resistor.cpp
        Capacitor.cpp
        Inductor.cpp
        Ground.cpp
        VoltageSource.cpp
        CurrentSource.cpp
        PulseSource.cpp
        DependentSource.cpp
        VCVS.cpp
        VCCS.cpp
        CCVS.cpp
        CCCS.cpp
        Circuit.cpp
        CircuitManager.cpp
)

