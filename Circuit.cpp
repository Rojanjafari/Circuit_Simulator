//
// Created by ASUS on 6/3/2025.
//

#include "Circuit.h"
#include <iostream>
#include <algorithm> 
#include <cctype>
#include <limits>
#include <set>

using namespace std;

Circuit::Circuit() {
}

CircuitElement* Circuit::findElement(const string& name) {
    for (const auto& element : elements) {
        if (element->getName() == name) {
            return element.get();
        }
    }
    return nullptr;
}

bool Circuit::elementExists(const string& name) const {
    for (const auto& element : elements) {
        if (element->getName() == name) {
            return true;
        }
    }
    return false;
}

bool Circuit::nodeExists(const string& nodeName) const {
    return nodes.count(CircuitElement::normalizeNodeName(nodeName));
}

void Circuit::addResistor(const string& name, const string& node1, const string& node2, const string& valueStr) {
    if (elementExists(name)) {
        cerr << "Error: Resistor " << name << " already exists in the circuit." << endl;
        return;
    }
    try {
        double value = Resistor::parseValue(valueStr);
        elements.push_back(make_unique<Resistor>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        cout << "Resistor " << name << " added successfully." << endl;
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        cerr << "Correct format: add R<name> <node1> <node2> <value>." << endl;
    } catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
}

void Circuit::addCapacitor(const string& name, const string& node1, const string& node2, const string& valueStr) {
    if (elementExists(name)) {
        cerr << "Error: Capacitor " << name << " already exists in the circuit." << endl;
        return;
    }
    try {
        double value = Capacitor::parseValue(valueStr);
        elements.push_back(make_unique<Capacitor>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        cout << "Capacitor " << name << " added successfully." << endl;
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        cerr << "Correct format: add C<name> <node1> <node2> <value>." << endl;
    } catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
}

void Circuit::addInductor(const string& name, const string& node1, const string& node2, const string& valueStr) {
    if (elementExists(name)) {
        cerr << "Error: Inductor " << name << " already exists in the circuit." << endl;
        return;
    }
    try {
        double value = Inductor::parseValue(valueStr);
        elements.push_back(make_unique<Inductor>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        cout << "Inductor " << name << " added successfully." << endl;
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        cerr << "Correct format: add L<name> <node1> <node2> <value>." << endl;
    } catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
}

void Circuit::addGround(const string& node) {
    string normalizedNode = CircuitElement::normalizeNodeName(node);
    if (elementExists("GND")) {
        cerr << "Error: A ground element already exists in the circuit. Only one ground is supported." << endl;
        return;
    }
    if (nodeExists(normalizedNode)) {
        cerr << "Error: Node " << normalizedNode << " already exists. Ground cannot be added to an existing node that is not a dedicated ground node." << endl;
        return;
    }

    elements.push_back(make_unique<Ground>(normalizedNode));
    nodes.insert(normalizedNode);
    cout << "Ground added to node " << normalizedNode << " successfully." << endl;
}

void Circuit::deleteElement(const string& typePrefix, const string& name) {
    string fullElementName = typePrefix + name;

    auto it = remove_if(elements.begin(), elements.end(), [&](const unique_ptr<CircuitElement>& el) {
        return el->getName() == fullElementName;
    });

    if (it != elements.end()) {
        elements.erase(it, elements.end());
        cout << "Element " << fullElementName << " deleted successfully." << endl;
    } else {
        if (typePrefix == "R") {
            cerr << "Error: Cannot delete resistor; component not found." << endl;
        } else if (typePrefix == "C") {
            cerr << "Error: Cannot delete capacitor; component not found." << endl;
        } else if (typePrefix == "L") {
            cerr << "Error: Cannot delete inductor; component not found." << endl;
        } else if (typePrefix == "GND") {
            cerr << "Error: Node does not exist or Ground element not found." << endl;
        }
    }
}


void Circuit::listAllElements() const {
    if (elements.empty()) {
        cout << "No elements in the circuit." << endl;
        return;
    }
    cout << "--- All Elements ---" << endl;
    for (const auto& element : elements) {
        element->displayInfo();
    }
    cout << "--------------------" << endl;
}

void Circuit::listElementsByType(const string& type) const {
    bool found = false;
    cout << "--- " << type << " Elements ---" << endl;
    for (const auto& element : elements) {
        string elementType = element->getType();
        transform(elementType.begin(), elementType.end(), elementType.begin(), ::tolower);
        string searchType = type;
        transform(searchType.begin(), searchType.end(), searchType.begin(), ::tolower);

        if (elementType == searchType) {
            element->displayInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "No " << type << " elements found." << endl;
    }
    cout << "--------------------" << endl;
}

void Circuit::listNodes() const {
    if (nodes.empty()) {
        cout << "No nodes in the circuit." << endl;
        return;
    }
    cout << "Available nodes: ";
    bool first = true;
    for (const auto& node : nodes) {
        if (!first) {
            cout << ", ";
        }
        cout << node;
        first = false;
    }
    cout << endl;
}

void Circuit::renameNode(const string& oldName, const string& newName) {
    string normalizedOldName = CircuitElement::normalizeNodeName(oldName);
    string normalizedNewName = CircuitElement::normalizeNodeName(newName);

    if (!nodeExists(normalizedOldName)) {
        cerr << "ERROR: Node " << normalizedOldName << " does not exist in the circuit." << endl;
        return;
    }

    if (nodeExists(normalizedNewName)) {
        cerr << "ERROR: Node name " << normalizedNewName << " already exists." << endl;
        return;
    }

    nodes.erase(normalizedOldName);
    nodes.insert(normalizedNewName);

    for (const auto& element : elements) {
        if (element->getNode1() == normalizedOldName) {
        }
        if (element->getNode2() == normalizedOldName) {
        }
    }
    cout << "SUCCESS: Node renamed from " << normalizedOldName << " to " << normalizedNewName << "." << endl;
}

bool Circuit::isValidPrintVariable(const string& varName) {
    if (varName.length() < 2)
        return false;

    if (varName[0] == 'V' && varName[1] == '(' && varName.back() == ')') {
        string node_name = varName.substr(2, varName.length() - 3);
        if (!nodeExists(node_name)) {
            cerr << "Error: Node " << node_name << " not found in circuit." << endl;
            return false;
        }
        return true;
    }
    else if (varName[0] == 'I' && varName[1] == '(' && varName.back() == ')') {
        string component_name = varName.substr(2, varName.length() - 3);
        if (!elementExists(component_name)) {
            cerr << "Error: Component " << component_name << " not found in circuit." << endl;
            return false;
        }
        return true;
    }
    return false;
}

void Circuit::printOutput(const string& analysisType, const vector<string>& analysisParams, const vector<string>& variables) {
    cout << "--- Print Output ---" << endl;
    cout << "Analysis Type: " << analysisType << endl;

    if (analysisType == "TRAN") {
        if (analysisParams.size() < 2 || analysisParams.size() > 4) {
            cerr << "Error: Invalid number of parameters for TRAN analysis. Expected: <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>]." << endl;
            return;
        }

        for (const string& param : analysisParams) {
            try {
                stod(param);
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid numeric parameter for TRAN analysis: " << param << "." << endl;
                return;
            } catch (const out_of_range& e) {
                cerr << "Error: TRAN analysis parameter out of range: " << param << "." << endl;
                return;
            }
        }
    } else if (analysisType == "DC") {
        if (analysisParams.size() != 4) {
            cerr << "Error: Invalid number of parameters for DC analysis. Expected: <SourceName> <Start Value> <EndValue> <Increment>." << endl;
            return;
        }

        for (size_t i = 1; i < analysisParams.size(); ++i) {
            try {
                stod(analysisParams[i]);
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid numeric parameter for DC analysis: " << analysisParams[i] << "." << endl;
                return;
            } catch (const out_of_range& e) {
                cerr << "Error: DC analysis parameter out of range: " << analysisParams[i] << "." << endl;
                return;
            }
        }
    } else {
        cerr << "Error: Unsupported analysis type: " << analysisType << "." << endl;
        return;
    }

    cout << "Analysis Parameters: ";
    for (const auto& param : analysisParams) {
        cout << param << " ";
    }
    cout << endl;

    cout << "Variables to display:" << endl;
    for (const auto& var : variables) {
        if (isValidPrintVariable(var)) {
            cout << "  - " << var << " (Valid)" << endl;
        } else {
            cerr << "Error: One or more print variables are invalid. Cannot proceed with print command." << endl;
            cout << "--------------------" << endl;
            return;
        }
    }
    cout << "--------------------" << endl;
}