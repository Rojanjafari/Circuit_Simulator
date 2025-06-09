

#include "Inductor.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Inductor::Inductor(const std::string& name, const std::string& node1, const std::string& node2, double value)
        : CircuitElement(name, node1, node2) {
    if (value <= 0) {
        throw std::invalid_argument("Error: Inductance cannot be zero or negative.");
    }
    this->value = value;
}

double Inductor::getValue() const {
    return value;
}

void Inductor::displayInfo() const {
    std::cout << "Inductor: " << name << ", Nodes: " << node1 << " - " << node2 << ", Value: " << value << " Henries" << std::endl;
}

std::string Inductor::getType() const {
    return "Inductor";
}

double Inductor::parseValue(const std::string& valueStr) {
    std::string cleanedStr = valueStr;
    std::transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = std::string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('h')) != std::string::npos) {
        if (unitPos == cleanedStr.length() - 1) {
            cleanedStr = cleanedStr.substr(0, unitPos);
        }
    } else if ((unitPos = cleanedStr.find("mh")) != std::string::npos || (unitPos = cleanedStr.find('m')) != std::string::npos) {
        multiplier = 1e-3;
    } else if ((unitPos = cleanedStr.find("uh")) != std::string::npos || (unitPos = cleanedStr.find('u')) != std::string::npos) {
        multiplier = 1e-6;
    } else if ((unitPos = cleanedStr.find("nh")) != std::string::npos || (unitPos = cleanedStr.find('n')) != std::string::npos) {
        multiplier = 1e-9;
    } else if ((unitPos = cleanedStr.find("ph")) != std::string::npos || (unitPos = cleanedStr.find('p')) != std::string::npos) {
        multiplier = 1e-12;
    }

    try {
        if (unitPos != std::string::npos) {
            return std::stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return std::stod(cleanedStr);
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: Invalid inductance value format.");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Error: Inductance value out of range.");
    }
}