#ifndef CIRCUIT_SIMULATOR_CIRCUITMANAGER_H
#define CIRCUIT_SIMULATOR_CIRCUITMANAGER_H


#include <string>
#include <vector>
#include <map>
#include "Circuit.h"

class CircuitManager {
private:


    std::map<int, std::string> availableSchematics;
    std::string schematicsDirectory = "schematics/";


    void populateAvailableSchematics();

public:
    CircuitManager();



    std::string chooseExistingSchematic();


    bool loadCircuitFromFile(const std::string& filePath, Circuit& circuit);


    void addNewSchematic(const std::string& filePath);
};


#endif
