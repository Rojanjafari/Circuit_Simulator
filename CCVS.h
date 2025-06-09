#ifndef CIRCUIT_SIMULATOR_CCVS_H
#define CIRCUIT_SIMULATOR_CCVS_H


#include "DependentSource.h"

class CCVS : public DependentSource {
public:
    CCVS(const std::string& name, const std::string& node1, const std::string& node2,
         const std::string& controlVoltageSourceName, double gain);

    void displayInfo() const override;
    std::string getType() const override;
};


#endif
