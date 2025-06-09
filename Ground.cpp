#include "Ground.h"
#include <iostream>

Ground::Ground(const std::string& node)
        : CircuitElement("GND", node) {}

void Ground::displayInfo() const {
    std::cout << "Ground: Node: " << node1 << std::endl;
}

std::string Ground::getType() const {
    return "Ground";
}
