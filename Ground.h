#ifndef CIRCUIT_SIMULATOR_GROUND_H
#define CIRCUIT_SIMULATOR_GROUND_H


#include "CircuitElement.h"

class Ground : public CircuitElement {
public:
    Ground(const std::string& node);

    void displayInfo() const override;
    std::string getType() const override;
};


#endif 
