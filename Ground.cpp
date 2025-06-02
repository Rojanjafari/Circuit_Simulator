//
// Created by ASUS on 6/3/2025.
//

#include "Ground.h"
#include <iostream>

using namespace std;

Ground::Ground(const string& node)
        : CircuitElement("GND", node) {}

void Ground::displayInfo() const {
    cout << "Ground: Node: " << node1 << endl;
}

string Ground::getType() const {
    return "Ground";
}