#ifndef CIRCUIT_SIMULATOR_CCCS_H
#define CIRCUIT_SIMULATOR_CCCS_H


#include "DependentSource.h"

class CCCS : public DependentSource {
public:
    CCCS(const std::string& name, const std::string& node1, const std::string& node2,
         const std::string& controlVoltageSourceName, double gain);

    void displayInfo() const override;
    std::string getType() const override;
};


#endif
