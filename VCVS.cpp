#include "VCVS.h"
#include <iostream>

VCVS::VCVS(const std::string& name, const std::string& node1, const std::string& node2,
           const std::string& controlNode1, const std::string& controlNode2, double gain)
        : DependentSource(name, node1, node2, controlNode1, controlNode2, gain) {}

void VCVS::displayInfo() const {
    std::cout << "VCVS (Voltage-Controlled Voltage Source): " << name << ", Nodes: " << node1 << " (+) - " << node2
              << " (-), Control Nodes: " << controlNode1 << " - " << controlNode2 << ", Gain: " << gain << std::endl;
}

std::string VCVS::getType() const {
    return "VCVS";
}