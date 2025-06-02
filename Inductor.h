//
// Created by ASUS on 6/3/2025.
//

#ifndef CIRCUIT_SIMULATOR_INDUCTOR_H
#define CIRCUIT_SIMULATOR_INDUCTOR_H

#include "CircuitElement.h"
#include <stdexcept>

using namespace std;

class Inductor : public CircuitElement {
private:
    double value;

public:
    Inductor(const string& name, const string& node1, const string& node2, double value);

    double getValue() const;
    void displayInfo() const override;
    string getType() const override;

    static double parseValue(const string& valueStr);
};


#endif //CIRCUIT_SIMULATOR_INDUCTOR_H