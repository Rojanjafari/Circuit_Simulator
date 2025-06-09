#include "Capacitor.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Capacitor::Capacitor(const std::string& name, const std::string& node1, const std::string& node2, double value)
        : CircuitElement(name, node1, node2) {
    if (value <= 0) {
        throw std::invalid_argument("Error: Capacitance cannot be zero or negative.");
    }
    this->value = value;
}

double Capacitor::getValue() const {
    return value;
}

void Capacitor::displayInfo() const {
    std::cout << "Capacitor: " << name << ", Nodes: " << node1 << " - " << node2 << ", Value: " << value << " Farads" << std::endl;
}

std::string Capacitor::getType() const {
    return "Capacitor";
}

double Capacitor::parseValue(const std::string& valueStr) {
    std::string cleanedStr = valueStr;
    std::transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = std::string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('f')) != std::string::npos) {
        if (unitPos == cleanedStr.length() - 1) {
            cleanedStr = cleanedStr.substr(0, unitPos);
        }
    } else if ((unitPos = cleanedStr.find("uf")) != std::string::npos || (unitPos = cleanedStr.find('u')) != std::string::npos) {
        multiplier = 1e-6;
    } else if ((unitPos = cleanedStr.find("nf")) != std::string::npos || (unitPos = cleanedStr.find('n')) != std::string::npos) {
        multiplier = 1e-9;
    } else if ((unitPos = cleanedStr.find("pf")) != std::string::npos || (unitPos = cleanedStr.find('p')) != std::string::npos) {
        multiplier = 1e-12;
    }

    try {
        if (unitPos != std::string::npos) {
            return std::stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return std::stod(cleanedStr);
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: Invalid capacitance value format.");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Error: Capacitance value out of range.");
    }
}