#ifndef CIRCUIT_SIMULATOR_CIRCUIT_H
#define CIRCUIT_SIMULATOR_CIRCUIT_H


#include "CircuitElement.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Ground.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "PulseSource.h"
#include "VCVS.h"
#include "VCCS.h"
#include "CCVS.h"
#include "CCCS.h"

#include <vector>
#include <string>
#include <memory>
#include <set>
#include <map>

class CircuitManager;

class Circuit {
private:
    std::vector<std::unique_ptr<CircuitElement>> elements;
    std::set<std::string> nodes;


    CircuitElement* findElement(const std::string& name);


    bool isValidPrintVariable(const std::string& varName);

public:
    Circuit();
    ~Circuit() = default;


    void clearElements();
    bool elementExists(const std::string& name) const;
    bool nodeExists(const std::string& nodeName) const;


    void addResistor(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr);
    void addCapacitor(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr);
    void addInductor(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr);
    void addGround(const std::string& node);
    void addVoltageSource(const std::string& name, const std::string& node1, const std::string& node2,
                          const std::string& type, const std::vector<std::string>& params);
    void addCurrentSource(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr);

    void addPulseSource(const std::string& name, const std::string& node1, const std::string& node2,
                        const std::string& type, const std::vector<std::string>& params);

    void addVCVS(const std::string& name, const std::string& node1, const std::string& node2,
                 const std::string& ctrlNode1, const std::string& ctrlNode2, const std::string& gainStr);
    void addVCCS(const std::string& name, const std::string& node1, const std::string& node2,
                 const std::string& ctrlNode1, const std::string& ctrlNode2, const std::string& gainStr);
    void addCCVS(const std::string& name, const std::string& node1, const std::string& node2,
                 const std::string& ctrlVoltageSourceName, const std::string& gainStr);
    void addCCCS(const std::string& name, const std::string& node1, const std::string& node2,
                 const std::string& ctrlVoltageSourceName, const std::string& gainStr);



    void deleteElement(const std::string& typePrefix, const std::string& name);


    void listAllElements() const;
    void listElementsByType(const std::string& type) const;


    void listNodes() const;
    void renameNode(const std::string& oldName, const std::string& newName);


    void printOutput(const std::string& analysisType, const std::vector<std::string>& analysisParams, const std::vector<std::string>& variables);


    friend class CircuitManager;
};


#endif 