#ifndef CIRCUIT_SIMULATOR_CAPACITOR_H
#define CIRCUIT_SIMULATOR_CAPACITOR_H

#include "CircuitElement.h"
#include <stdexcept>

class Capacitor : public CircuitElement {
private:
    double value;

public:
    Capacitor(const std::string& name, const std::string& node1, const std::string& node2, double value);

    double getValue() const;
    void displayInfo() const override;
    std::string getType() const override;


    static double parseValue(const std::string& valueStr);
};


#endif 