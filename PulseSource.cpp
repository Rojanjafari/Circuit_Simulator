#include "PulseSource.h"
#include <iostream>
#include <algorithm>
#include <cctype>

PulseSource::PulseSource(const std::string& name, const std::string& node1, const std::string& node2,
                         const std::string& typeStr, const std::vector<std::string>& params)
        : CircuitElement(name, node1, node2), typeString(typeStr), parameters(params) {
    type = parsePulseType(typeStr);

    if (params.empty()) {
        throw std::invalid_argument("Error: Missing parameters for time-dependent source (PULSE).");
    }

}

void PulseSource::displayInfo() const {
    std::cout << "Pulse Source: " << name << ", Nodes: " << node1 << " (+) - " << node2 << " (-), Type: " << typeString << ", Parameters: ";
    for (const auto& param : parameters) {
        std::cout << param << " ";
    }
    std::cout << std::endl;
}

std::string PulseSource::getType() const {
    return "PulseSource";
}

PulseSource::PulseType PulseSource::getPulseType() const {
    return type;
}

const std::string& PulseSource::getTypeString() const {
    return typeString;
}

const std::vector<std::string>& PulseSource::getParameters() const {
    return parameters;
}

PulseSource::PulseType PulseSource::parsePulseType(const std::string& typeStr) {
    std::string lowerTypeStr = typeStr;
    std::transform(lowerTypeStr.begin(), lowerTypeStr.end(), lowerTypeStr.begin(), ::tolower);
    if (lowerTypeStr == "step") {
        return PulseType::STEP;
    } else if (lowerTypeStr == "square") {
        return PulseType::SQUARE;
    } else if (lowerTypeStr == "triangle") {
        return PulseType::TRIANGLE;
    }

    return PulseType::UNDEFINED;
}
