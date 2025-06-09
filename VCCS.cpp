#include "VCCS.h"
#include <iostream>

VCCS::VCCS(const std::string& name, const std::string& node1, const std::string& node2,
           const std::string& controlNode1, const std::string& controlNode2, double gain)
        : DependentSource(name, node1, node2, controlNode1, controlNode2, gain) {}

void VCCS::displayInfo() const {
    std::cout << "VCCS (Voltage-Controlled Current Source): " << name << ", Nodes: " << node1 << " (Source) - " << node2
              << " (Drain), Control Nodes: " << controlNode1 << " - " << controlNode2 << ", Transconductance (Gain): " << gain << " A/V" << std::endl;
}

std::string VCCS::getType() const {
    return "VCCS";
}