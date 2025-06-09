#include "CCVS.h"
#include <iostream>

CCVS::CCVS(const std::string& name, const std::string& node1, const std::string& node2,
           const std::string& controlVoltageSourceName, double gain)
        : DependentSource(name, node1, node2, controlVoltageSourceName, gain) {}

void CCVS::displayInfo() const {
    std::cout << "CCVS (Current-Controlled Voltage Source): " << name << ", Nodes: " << node1 << " (+) - " << node2
              << " (-), Control Source: " << controlVoltageSourceName << ", Transresistance (Gain): " << gain << " V/A" << std::endl;
}

std::string CCVS::getType() const {
    return "CCVS";
}