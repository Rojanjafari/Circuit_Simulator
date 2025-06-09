//
// Created by ASUS on 6/3/2025.
//

#ifndef CIRCUIT_SIMULATOR_CIRCUITMANAGER_H
#define CIRCUIT_SIMULATOR_CIRCUITMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "Circuit.h"

using namespace std;

class CircuitManager {
private:
    map<int, string> availableSchematics;
    string schematicsDirectory = "schematics";

    void populateAvailableSchematics();

public:
    CircuitManager();

    string chooseExistingSchematic();

    bool loadCircuitFromFile(const string& filePath, Circuit& circuit);

    void addNewSchematic(const string& filePath);
};


#endif //CIRCUIT_SIMULATOR_CIRCUITMANAGER_H