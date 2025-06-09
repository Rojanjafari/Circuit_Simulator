#include "CCCS.h"
#include <iostream>

CCCS::CCCS(const std::string& name, const std::string& node1, const std::string& node2,
           const std::string& controlVoltageSourceName, double gain)
        : DependentSource(name, node1, node2, controlVoltageSourceName, gain) {}

void CCCS::displayInfo() const {
    std::cout << "CCCS (Current-Controlled Current Source): " << name << ", Nodes: " << node1 << " (Source) - " << node2
              << " (Drain), Control Source: " << controlVoltageSourceName << ", Current Gain: " << gain << " A/A" << std::endl;
}

std::string CCCS::getType() const {
    return "CCCS";
}