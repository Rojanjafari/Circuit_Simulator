//
// Created by ASUS on 6/3/2025.
//

#include "Resistor.h"
#include <iostream>
#include <algorithm> 
#include <cctype>  

using namespace std;

Resistor::Resistor(const string& name, const string& node1, const string& node2, double value)
        : CircuitElement(name, node1, node2) {
    if (value <= 0) {
        throw invalid_argument("Error: Resistance cannot be zero or negative.");
    }
    this->value = value;
}

double Resistor::getValue() const {
    return value;
}

void Resistor::displayInfo() const {
    cout << "Resistor: " << name << ", Nodes: " << node1 << " - " << node2 << ", Value: " << value << " Ohms" << endl;
}

string Resistor::getType() const {
    return "Resistor";
}

double Resistor::parseValue(const string& valueStr) {
    string cleanedStr = valueStr;
    transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('k')) != string::npos) {
        multiplier = 1e3;
    } else if ((unitPos = cleanedStr.find("meg")) != string::npos || (unitPos = cleanedStr.find("mn")) != string::npos) {
        multiplier = 1e6;
    } else if (cleanedStr.find('m') != string::npos) {
    }

    try {
        if (unitPos != string::npos) {
            return stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return stod(cleanedStr);
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Error: Invalid resistance value format.");
    } catch (const out_of_range& e) {
        throw out_of_range("Error: Resistance value out of range.");
    }
}