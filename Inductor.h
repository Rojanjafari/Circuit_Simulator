#ifndef CIRCUIT_SIMULATOR_INDUCTOR_H
#define CIRCUIT_SIMULATOR_INDUCTOR_H

#include "CircuitElement.h"
#include <stdexcept>

class Inductor : public CircuitElement {
private:
    double value;

public:
    Inductor(const std::string& name, const std::string& node1, const std::string& node2, double value);

    double getValue() const;
    void displayInfo() const override;
    std::string getType() const override;


    static double parseValue(const std::string& valueStr);
};


#endif 