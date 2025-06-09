#include "Resistor.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Resistor::Resistor(const std::string& name, const std::string& node1, const std::string& node2, double value)
        : CircuitElement(name, node1, node2) {
    if (value <= 0) {
        throw std::invalid_argument("Error: Resistance cannot be zero or negative.");
    }
    this->value = value;
}

double Resistor::getValue() const {
    return value;
}

void Resistor::displayInfo() const {
    std::cout << "Resistor: " << name << ", Nodes: " << node1 << " - " << node2 << ", Value: " << value << " Ohms" << std::endl;
}

std::string Resistor::getType() const {
    return "Resistor";
}

double Resistor::parseValue(const std::string& valueStr) {
    std::string cleanedStr = valueStr;
    std::transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = std::string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('k')) != std::string::npos) {
        multiplier = 1e3;
    } else if ((unitPos = cleanedStr.find("meg")) != std::string::npos || (unitPos = cleanedStr.find("mn")) != std::string::npos) {
        multiplier = 1e6;
    }

    try {
        if (unitPos != std::string::npos) {
            return std::stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return std::stod(cleanedStr);
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: Invalid resistance value format.");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Error: Resistance value out of range.");
    }
}