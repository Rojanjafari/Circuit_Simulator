#include "CircuitElement.h"
#include <cctype>

CircuitElement::CircuitElement(const std::string& name, const std::string& node1, const std::string& node2)
        : name(name), node1(normalizeNodeName(node1)), node2(normalizeNodeName(node2)) {}

const std::string& CircuitElement::getName() const {
    return name;
}

const std::string& CircuitElement::getNode1() const {
    return node1;
}

const std::string& CircuitElement::getNode2() const {
    return node2;
}

std::string CircuitElement::normalizeNodeName(const std::string& node) {
    if (node.empty()) {
        return "";
    }
    std::string normalized = node;


    if (normalized.length() > 1 && (normalized[0] == 'n' || normalized[0] == 'N') && std::isdigit(normalized[1])) {
        for (char &c : normalized) {
            c = static_cast<char>(std::toupper(c));
        }
    }
    return normalized;
}