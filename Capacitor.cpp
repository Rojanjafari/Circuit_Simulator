//
// Created by ASUS on 6/3/2025.
//

#include "Capacitor.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

Capacitor::Capacitor(const string& name, const string& node1, const string& node2, double value)
        : CircuitElement(name, node1, node2) {
    if (value <= 0) {
        throw invalid_argument("Error: Capacitance cannot be zero or negative.");
    }
    this->value = value;
}

double Capacitor::getValue() const {
    return value;
}

void Capacitor::displayInfo() const {
    cout << "Capacitor: " << name << ", Nodes: " << node1 << " - " << node2 << ", Value: " << value << " Farads" << endl;
}

string Capacitor::getType() const {
    return "Capacitor";
}

double Capacitor::parseValue(const string& valueStr) {
    string cleanedStr = valueStr;
    transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('f')) != string::npos) {
        if (unitPos == cleanedStr.length() - 1) {
            cleanedStr = cleanedStr.substr(0, unitPos);
        }
    } else if ((unitPos = cleanedStr.find("uf")) != string::npos || (unitPos = cleanedStr.find('u')) != string::npos) {
        multiplier = 1e-6;
    } else if ((unitPos = cleanedStr.find("nf")) != string::npos || (unitPos = cleanedStr.find('n')) != string::npos) {
        multiplier = 1e-9;
    } else if ((unitPos = cleanedStr.find("pf")) != string::npos || (unitPos = cleanedStr.find('p')) != string::npos) {
        multiplier = 1e-12;
    }

    try {
        if (unitPos != string::npos) {
            return stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return stod(cleanedStr);
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Error: Invalid capacitance value format.");
    } catch (const out_of_range& e) {
        throw out_of_range("Error: Capacitance value out of range.");
    }
}