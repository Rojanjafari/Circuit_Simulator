#ifndef CIRCUIT_SIMULATOR_VCCS_H
#define CIRCUIT_SIMULATOR_VCCS_H


#include "DependentSource.h"

class VCCS : public DependentSource {
public:
    VCCS(const std::string& name, const std::string& node1, const std::string& node2,
         const std::string& controlNode1, const std::string& controlNode2, double gain);

    void displayInfo() const override;
    std::string getType() const override;
};


#endif 