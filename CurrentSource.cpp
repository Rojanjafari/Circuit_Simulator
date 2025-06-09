#include "CurrentSource.h"
#include <iostream>
#include <algorithm>
#include <cctype>

CurrentSource::CurrentSource(const std::string& name, const std::string& node1, const std::string& node2, double value)
        : CircuitElement(name, node1, node2), value(value) {
}

void CurrentSource::displayInfo() const {
    std::cout << "Current Source (Independent): " << name << ", Nodes: " << node1 << " (Source) - " << node2 << " (Drain), Value: " << value << " A" << std::endl;
}

std::string CurrentSource::getType() const {
    return "CurrentSource";
}

double CurrentSource::getValue() const {
    return value;
}

double CurrentSource::parseValue(const std::string& valueStr) {
    std::string cleanedStr = valueStr;
    std::transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = std::string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('a')) != std::string::npos) {
        if (unitPos == cleanedStr.length() - 1) {
            cleanedStr = cleanedStr.substr(0, unitPos);
        }
    } else if ((unitPos = cleanedStr.find("ma")) != std::string::npos || (unitPos = cleanedStr.find('m')) != std::string::npos) {
        multiplier = 1e-3;
    } else if ((unitPos = cleanedStr.find("ua")) != std::string::npos || (unitPos = cleanedStr.find('u')) != std::string::npos) {
        multiplier = 1e-6;
    } else if ((unitPos = cleanedStr.find("na")) != std::string::npos || (unitPos = cleanedStr.find('n')) != std::string::npos) {
        multiplier = 1e-9;
    } else if ((unitPos = cleanedStr.find("pa")) != std::string::npos || (unitPos = cleanedStr.find('p')) != std::string::npos) {
        multiplier = 1e-12;
    }

    try {
        if (unitPos != std::string::npos) {
            return std::stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return std::stod(cleanedStr);
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: Invalid current value format.");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Error: Current value out of range.");
    }
}
