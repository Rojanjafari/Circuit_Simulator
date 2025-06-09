#ifndef CIRCUIT_SIMULATOR_VOLTAGESOURCE_H
#define CIRCUIT_SIMULATOR_VOLTAGESOURCE_H


#include "CircuitElement.h"
#include <string>
#include <stdexcept>


enum class VoltageSourceType {
    DC,
    SIN
};

class VoltageSource : public CircuitElement {
private:
    VoltageSourceType sourceType;
    double dcValue;
    double vOffset;
    double vAmplitude;
    double frequency;

public:

    VoltageSource(const std::string& name, const std::string& node1, const std::string& node2, double value);


    VoltageSource(const std::string& name, const std::string& node1, const std::string& node2,
                  double vOffset, double vAmplitude, double frequency);

    void displayInfo() const override;
    std::string getType() const override;

    VoltageSourceType getSourceType() const;
    double getDcValue() const;
    double getVoffset() const;
    double getVamplitude() const;
    double getFrequency() const;


    static double parseValue(const std::string& valueStr);
};


#endif
