//
// Created by ASUS on 6/3/2025.
//

#ifndef CIRCUIT_SIMULATOR_GROUND_H
#define CIRCUIT_SIMULATOR_GROUND_H

#include "CircuitElement.h"

using namespace std;

class Ground : public CircuitElement {
public:
    Ground(const string& node);

    void displayInfo() const override;
    string getType() const override;
};


#endif //CIRCUIT_SIMULATOR_GROUND_H