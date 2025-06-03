//
// Created by ASUS on 6/3/2025.
//

#ifndef CIRCUIT_SIMULATOR_CIRCUIT_H
#define CIRCUIT_SIMULATOR_CIRCUIT_H

#include "CircuitElement.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Ground.h"
#include <vector>
#include <string>
#include <memory> 
#include <set>
#include <map>

using namespace std;

class Circuit {
private:
    vector<unique_ptr<CircuitElement>> elements;
    set<string> nodes;

    CircuitElement* findElement(const string& name);

    bool isValidPrintVariable(const string& varName);

public:
    Circuit();
    ~Circuit() = default;

    void addResistor(const string& name, const string& node1, const string& node2, const string& valueStr);
    void addCapacitor(const string& name, const string& node1, const string& node2, const string& valueStr);
    void addInductor(const string& name, const string& node1, const string& node2, const string& valueStr);
    void addGround(const string& node);

    void deleteElement(const string& typePrefix, const string& name);

    void listAllElements() const;
    void listElementsByType(const string& type) const;

    void listNodes() const;
    void renameNode(const string& oldName, const string& newName);

    bool elementExists(const string& name) const;

    bool nodeExists(const string& nodeName) const;

    void printOutput(const string& analysisType, const vector<string>& analysisParams, const vector<string>& variables);
};


#endif //CIRCUIT_SIMULATOR_CIRCUIT_H
