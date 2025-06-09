#include "VoltageSource.h"
#include <iostream>
#include <algorithm>
#include <cctype>

VoltageSource::VoltageSource(const std::string& name, const std::string& node1, const std::string& node2, double value)
        : CircuitElement(name, node1, node2), sourceType(VoltageSourceType::DC), dcValue(value),
          vOffset(0.0), vAmplitude(0.0), frequency(0.0) {


}

VoltageSource::VoltageSource(const std::string& name, const std::string& node1, const std::string& node2,
                             double vOffset, double vAmplitude, double frequency)
        : CircuitElement(name, node1, node2), sourceType(VoltageSourceType::SIN), dcValue(0.0),
          vOffset(vOffset), vAmplitude(vAmplitude), frequency(frequency) {

    if (vAmplitude < 0) {
        throw std::invalid_argument("Error: Vamplitude cannot be negative for sinusoidal source.");
    }
    if (frequency < 0) {
        throw std::invalid_argument("Error: Frequency cannot be negative for sinusoidal source.");
    }
}

void VoltageSource::displayInfo() const {
    if (sourceType == VoltageSourceType::DC) {
        std::cout << "Voltage Source (DC): " << name << ", Nodes: " << node1 << " (+) - " << node2 << " (-), Value: " << dcValue << " V" << std::endl;
    } else {
        std::cout << "Voltage Source (SIN): " << name << ", Nodes: " << node1 << " (+) - " << node2 << " (-), Voffset: " << vOffset
                  << "V, Vamplitude: " << vAmplitude << "V, Frequency: " << frequency << "Hz" << std::endl;
    }
}

std::string VoltageSource::getType() const {
    return "VoltageSource";
}

VoltageSourceType VoltageSource::getSourceType() const {
    return sourceType;
}

double VoltageSource::getDcValue() const {
    return dcValue;
}

double VoltageSource::getVoffset() const {
    return vOffset;
}

double VoltageSource::getVamplitude() const {
    return vAmplitude;
}

double VoltageSource::getFrequency() const {
    return frequency;
}


double VoltageSource::parseValue(const std::string& valueStr) {
    try {
        return std::stod(valueStr);
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: Invalid voltage value format.");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Error: Voltage value out of range.");
    }
}
