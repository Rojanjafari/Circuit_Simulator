//
// Created by ASUS on 6/3/2025.
//

#ifndef CIRCUIT_SIMULATOR_RESISTOR_H
#define CIRCUIT_SIMULATOR_RESISTOR_H

#include "CircuitElement.h"
#include <stdexcept>

using namespace std;

class Resistor : public CircuitElement {
private:
    double value;

public:
    Resistor(const string& name, const string& node1, const string& node2, double value);

    double getValue() const;
    void displayInfo() const override;
    string getType() const override;

    static double parseValue(const string& valueStr);
};


#endif //CIRCUIT_SIMULATOR_RESISTOR_H