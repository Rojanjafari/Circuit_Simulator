//
// Created by ASUS on 6/3/2025.
//

#include "Inductor.h"
#include <iostream>
#include <algorithm> 
#include <cctype>    

using namespace std;

Inductor::Inductor(const string& name, const string& node1, const string& node2, double value)
        : CircuitElement(name, node1, node2) {
    if (value <= 0) {
        throw invalid_argument("Error: Inductance cannot be zero or negative.");
    }
    this->value = value;
}

double Inductor::getValue() const {
    return value;
}

void Inductor::displayInfo() const {
    cout << "Inductor: " << name << ", Nodes: " << node1 << " - " << node2 << ", Value: " << value << " Henries" << endl;
}

string Inductor::getType() const {
    return "Inductor";
}

double Inductor::parseValue(const string& valueStr) {
    string cleanedStr = valueStr;
    transform(cleanedStr.begin(), cleanedStr.end(), cleanedStr.begin(), ::tolower);

    size_t unitPos = string::npos;
    double multiplier = 1.0;

    if ((unitPos = cleanedStr.find('h')) != string::npos) {
        if (unitPos == cleanedStr.length() - 1) {
            cleanedStr = cleanedStr.substr(0, unitPos);
        }
    } else if ((unitPos = cleanedStr.find("mh")) != string::npos || (unitPos = cleanedStr.find('m')) != string::npos) {
        multiplier = 1e-3;
    } else if ((unitPos = cleanedStr.find("uh")) != string::npos || (unitPos = cleanedStr.find('u')) != string::npos) {
        multiplier = 1e-6;
    } else if ((unitPos = cleanedStr.find("nh")) != string::npos || (unitPos = cleanedStr.find('n')) != string::npos) {
        multiplier = 1e-9;
    } else if ((unitPos = cleanedStr.find("ph")) != string::npos || (unitPos = cleanedStr.find('p')) != string::npos) {
        multiplier = 1e-12;
    }

    try {
        if (unitPos != string::npos) {
            return stod(cleanedStr.substr(0, unitPos)) * multiplier;
        } else {
            return stod(cleanedStr);
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Error: Invalid inductance value format.");
    } catch (const out_of_range& e) {
        throw out_of_range("Error: Inductance value out of range.");
    }
}