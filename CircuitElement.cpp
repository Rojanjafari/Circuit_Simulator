//
// Created by ASUS on 6/3/2025.
//

#include "CircuitElement.h"
#include <cctype>

using namespace std;

CircuitElement::CircuitElement(const string& name, const string& node1, const string& node2)
        : name(name), node1(normalizeNodeName(node1)), node2(normalizeNodeName(node2)) {}

const string& CircuitElement::getName() const {
    return name;
}

const string& CircuitElement::getNode1() const {
    return node1;
}

const string& CircuitElement::getNode2() const {
    return node2;
}

string CircuitElement::normalizeNodeName(const string& node) {
    if (node.empty()) {
        return "";
    }
    string normalized = node;
    if (normalized.length() > 1 && (normalized[0] == 'n' || normalized[0] == 'N') && isdigit(normalized[1])) {
        for (char &c : normalized) {
            c = static_cast<char>(toupper(c));
        }
    }
    return normalized;
}