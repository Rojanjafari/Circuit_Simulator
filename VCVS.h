#ifndef CIRCUIT_SIMULATOR_VCVS_H
#define CIRCUIT_SIMULATOR_VCVS_H


#include "DependentSource.h"

class VCVS : public DependentSource {
public:
    VCVS(const std::string& name, const std::string& node1, const std::string& node2,
         const std::string& controlNode1, const std::string& controlNode2, double gain);

    void displayInfo() const override;
    std::string getType() const override;
};


#endif
