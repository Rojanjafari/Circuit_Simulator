
#include "Circuit.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <set>

Circuit::Circuit() {


}

void Circuit::clearElements() {
    elements.clear();
    nodes.clear();
    std::cout << "Circuit cleared." << std::endl;
}

CircuitElement* Circuit::findElement(const std::string& name) {
    for (const auto& element : elements) {
        if (element->getName() == name) {
            return element.get();
        }
    }
    return nullptr;
}

bool Circuit::elementExists(const std::string& name) const {
    for (const auto& element : elements) {
        if (element->getName() == name) {
            return true;
        }
    }
    return false;
}

bool Circuit::nodeExists(const std::string& nodeName) const {
    return nodes.count(CircuitElement::normalizeNodeName(nodeName));
}

void Circuit::addResistor(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    try {
        double value = Resistor::parseValue(valueStr);
        elements.push_back(std::make_unique<Resistor>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "Resistor " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Negative or zero value for a component is invalid. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Invalid value out of range for resistor. ") + e.what());
    }
}

void Circuit::addCapacitor(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    try {
        double value = Capacitor::parseValue(valueStr);
        elements.push_back(std::make_unique<Capacitor>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "Capacitor " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Negative or zero value for a component is invalid. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Invalid value out of range for capacitor. ") + e.what());
    }
}

void Circuit::addInductor(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    try {
        double value = Inductor::parseValue(valueStr);
        elements.push_back(std::make_unique<Inductor>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "Inductor " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Negative or zero value for a component is invalid. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Invalid value out of range for inductor. ") + e.what());
    }
}

void Circuit::addGround(const std::string& node) {
    std::string normalizedNode = CircuitElement::normalizeNodeName(node);
    if (elementExists("GND")) {

        std::cerr << "Warning: A ground element already exists in the circuit. Only one fixed 'GND' element is supported by this simulator." << std::endl;

    }



    if (nodes.empty()) {
        std::cout << "Note: Adding first ground at node " << normalizedNode << ", which will serve as the circuit's reference." << std::endl;
    }

    elements.push_back(std::make_unique<Ground>(normalizedNode));
    nodes.insert(normalizedNode);
    std::cout << "Ground added to node " << normalizedNode << " successfully." << std::endl;
}

void Circuit::addVoltageSource(const std::string& name, const std::string& node1, const std::string& node2,
                               const std::string& type, const std::vector<std::string>& params) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    try {
        if (type == "DC") {
            if (params.size() != 1) {
                throw std::invalid_argument("Error: Missing parameters for time-dependent source (DC Voltage).");
            }
            double value = VoltageSource::parseValue(params[0]);
            elements.push_back(std::make_unique<VoltageSource>(name, node1, node2, value));
        } else if (type == "SIN") {
            if (params.size() != 3) {
                throw std::invalid_argument("Error: Missing parameters for time-dependent source (SIN Voltage).");
            }
            double vOffset = std::stod(params[0]);
            double vAmplitude = std::stod(params[1]);
            double frequency = std::stod(params[2]);
            elements.push_back(std::make_unique<VoltageSource>(name, node1, node2, vOffset, vAmplitude, frequency));
        } else {
            throw std::invalid_argument("Error: Unsupported voltage source type: " + type + ".");
        }
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "Voltage source " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Invalid voltage source definition. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Value out of range for voltage source parameter. ") + e.what());
    }
}

void Circuit::addCurrentSource(const std::string& name, const std::string& node1, const std::string& node2, const std::string& valueStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    try {
        double value = CurrentSource::parseValue(valueStr);
        elements.push_back(std::make_unique<CurrentSource>(name, node1, node2, value));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "Current source " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Invalid current source definition. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Value out of range for current source parameter. ") + e.what());
    }
}

void Circuit::addPulseSource(const std::string& name, const std::string& node1, const std::string& node2,
                             const std::string& type, const std::vector<std::string>& params) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    try {
        elements.push_back(std::make_unique<PulseSource>(name, node1, node2, type, params));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "Pulse source " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Missing parameters for time-dependent source. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Value out of range for pulse source parameter. ") + e.what());
    }
}

void Circuit::addVCVS(const std::string& name, const std::string& node1, const std::string& node2,
                      const std::string& ctrlNode1, const std::string& ctrlNode2, const std::string& gainStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    if (!nodeExists(ctrlNode1) || !nodeExists(ctrlNode2)) {
        throw std::invalid_argument("Error: Dependent source has an undefined control element (control nodes not found).");
    }
    try {
        double gain = DependentSource::parseGain(gainStr);
        elements.push_back(std::make_unique<VCVS>(name, node1, node2, ctrlNode1, ctrlNode2, gain));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "VCVS " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Invalid dependent source definition. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Gain value out of range for VCVS. ") + e.what());
    }
}

void Circuit::addVCCS(const std::string& name, const std::string& node1, const std::string& node2,
                      const std::string& ctrlNode1, const std::string& ctrlNode2, const std::string& gainStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    if (!nodeExists(ctrlNode1) || !nodeExists(ctrlNode2)) {
        throw std::invalid_argument("Error: Dependent source has an undefined control element (control nodes not found).");
    }
    try {
        double gain = DependentSource::parseGain(gainStr);
        elements.push_back(std::make_unique<VCCS>(name, node1, node2, ctrlNode1, ctrlNode2, gain));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "VCCS " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Invalid dependent source definition. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Gain value out of range for VCCS. ") + e.what());
    }
}

void Circuit::addCCVS(const std::string& name, const std::string& node1, const std::string& node2,
                      const std::string& ctrlVoltageSourceName, const std::string& gainStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    if (!elementExists(ctrlVoltageSourceName) || findElement(ctrlVoltageSourceName)->getType() != "VoltageSource") {
        throw std::invalid_argument("Error: Dependent source has an undefined control element (control voltage source not found or not a voltage source).");
    }
    try {
        double gain = DependentSource::parseGain(gainStr);
        elements.push_back(std::make_unique<CCVS>(name, node1, node2, ctrlVoltageSourceName, gain));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "CCVS " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Invalid dependent source definition. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Gain value out of range for CCVS. ") + e.what());
    }
}

void Circuit::addCCCS(const std::string& name, const std::string& node1, const std::string& node2,
                      const std::string& ctrlVoltageSourceName, const std::string& gainStr) {
    if (elementExists(name)) {
        throw std::invalid_argument("Error: Duplicate node or component name detected: " + name + ".");
    }
    if (!elementExists(ctrlVoltageSourceName) || findElement(ctrlVoltageSourceName)->getType() != "VoltageSource") {
        throw std::invalid_argument("Error: Dependent source has an undefined control element (control voltage source not found or not a voltage source).");
    }
    try {
        double gain = DependentSource::parseGain(gainStr);
        elements.push_back(std::make_unique<CCCS>(name, node1, node2, ctrlVoltageSourceName, gain));
        nodes.insert(CircuitElement::normalizeNodeName(node1));
        nodes.insert(CircuitElement::normalizeNodeName(node2));
        std::cout << "CCCS " << name << " added successfully." << std::endl;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Error: Invalid dependent source definition. ") + e.what());
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string("Error: Gain value out of range for CCCS. ") + e.what());
    }
}


void Circuit::deleteElement(const std::string& typePrefix, const std::string& name) {
    std::string fullElementName = typePrefix + name;

    auto it = std::remove_if(elements.begin(), elements.end(), [&](const std::unique_ptr<CircuitElement>& el) {
        return el->getName() == fullElementName;
    });

    if (it != elements.end()) {
        elements.erase(it, elements.end());
        std::cout << "Element " << fullElementName << " deleted successfully." << std::endl;
    } else {

        if (typePrefix == "R") {
            std::cerr << "Error: Cannot delete resistor; component not found." << std::endl;
        } else if (typePrefix == "C") {
            std::cerr << "Error: Cannot delete capacitor; component not found." << std::endl;
        } else if (typePrefix == "L") {
            std::cerr << "Error: Cannot delete inductor; component not found." << std::endl;
        } else if (typePrefix == "V") {
            std::cerr << "Error: Cannot delete voltage source; component not found." << std::endl;
        } else if (typePrefix == "I") {
            std::cerr << "Error: Cannot delete current source; component not found." << std::endl;
        } else if (typePrefix == "VPULSE") {
            std::cerr << "Error: Cannot delete pulse source; component not found." << std::endl;
        } else if (typePrefix == "E" || typePrefix == "G" || typePrefix == "H" || typePrefix == "F") {
            std::cerr << "Error: Cannot delete dependent source; component not found." << std::endl;
        }
        else if (typePrefix == "GND") {
            std::string normalizedNode = CircuitElement::normalizeNodeName(name);
            auto ground_it = std::remove_if(elements.begin(), elements.end(), [&](const std::unique_ptr<CircuitElement>& el) {
                return el->getType() == "Ground" && el->getNode1() == normalizedNode;
            });
            if (ground_it != elements.end()) {
                elements.erase(ground_it, elements.end());
                nodes.erase(normalizedNode);
                std::cout << "Ground at node " << normalizedNode << " deleted successfully." << std::endl;
            } else {
                std::cerr << "Error: Node does not exist or Ground element not found." << std::endl;
            }
        }
    }
}


void Circuit::listAllElements() const {
    if (elements.empty()) {
        std::cout << "No elements in the circuit." << std::endl;
        return;
    }
    std::cout << "--- All Elements ---" << std::endl;
    for (const auto& element : elements) {
        element->displayInfo();
    }
    std::cout << "--------------------" << std::endl;
}

void Circuit::listElementsByType(const std::string& type) const {
    bool found = false;
    std::cout << "--- " << type << " Elements ---" << std::endl;
    for (const auto& element : elements) {
        std::string elementType = element->getType();
        std::transform(elementType.begin(), elementType.end(), elementType.begin(), ::tolower);
        std::string searchType = type;
        std::transform(searchType.begin(), searchType.end(), searchType.begin(), ::tolower);

        if (elementType == searchType) {
            element->displayInfo();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No " << type << " elements found." << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

void Circuit::listNodes() const {
    if (nodes.empty()) {
        std::cout << "No nodes in the circuit." << std::endl;
        return;
    }
    std::cout << "Available nodes: ";
    bool first = true;
    for (const auto& node : nodes) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << node;
        first = false;
    }
    std::cout << std::endl;
}

void Circuit::renameNode(const std::string& oldName, const std::string& newName) {
    std::string normalizedOldName = CircuitElement::normalizeNodeName(oldName);
    std::string normalizedNewName = CircuitElement::normalizeNodeName(newName);

    if (!nodeExists(normalizedOldName)) {
        std::cerr << "ERROR: Node " << normalizedOldName << " not found in circuit." << std::endl;
        return;
    }

    if (nodeExists(normalizedNewName)) {
        std::cerr << "ERROR: Duplicate node or component name detected: " << normalizedNewName << "." << std::endl;
        return;
    }


    nodes.erase(normalizedOldName);
    nodes.insert(normalizedNewName);




    std::cout << "SUCCESS: Node renamed from " << normalizedOldName << " to " << normalizedNewName << "." << std::endl;
}


bool Circuit::isValidPrintVariable(const std::string& varName) {
    if (varName.length() < 2) return false;


    if (varName[0] == 'V' && varName[1] == '(' && varName.back() == ')') {
        std::string node_name = varName.substr(2, varName.length() - 3);
        if (!nodeExists(node_name)) {
            std::cerr << "Error: Node " << node_name << " not found in circuit." << std::endl;
            return false;
        }
        return true;
    }

    else if (varName[0] == 'I' && varName[1] == '(' && varName.back() == ')') {
        std::string component_name = varName.substr(2, varName.length() - 3);
        if (!elementExists(component_name)) {
            std::cerr << "Error: Component " << component_name << " not found in circuit." << std::endl;
            return false;
        }
        return true;
    }
    return false;
}

void Circuit::printOutput(const std::string& analysisType, const std::vector<std::string>& analysisParams, const std::vector<std::string>& variables) {

    bool ground_found = false;
    for (const auto& node : nodes) {
        if (node == "GND" || node == "0") {
            ground_found = true;
            break;
        }
    }
    if (!ground_found) {
        std::cerr << "Error: No ground node detected in the circuit. Circuit cannot be analyzed without a reference ground." << std::endl;
        return;
    }


    std::cout << "--- Print Output ---" << std::endl;
    std::cout << "Analysis Type: " << analysisType << std::endl;

    if (analysisType == "TRAN") {
        if (analysisParams.size() < 2 || analysisParams.size() > 4) {
            std::cerr << "Error: Missing parameters for time-dependent source (TRAN analysis). Expected: <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>]." << std::endl;
            return;
        }
        for (const std::string& param : analysisParams) {
            try {
                std::stod(param);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid numeric parameter for TRAN analysis: " << param << ". " << e.what() << std::endl;
                return;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: TRAN analysis parameter out of range: " << param << ". " << e.what() << std::endl;
                return;
            }
        }
    } else if (analysisType == "DC") {
        if (analysisParams.size() != 4) {
            std::cerr << "Error: Missing parameters for DC analysis. Expected: <SourceName> <Start Value> <EndValue> <Increment>." << std::endl;
            return;
        }

        if (!elementExists(analysisParams[0])) {
            std::cerr << "Error: Component " << analysisParams[0] << " not found in circuit. Cannot perform DC sweep." << std::endl;
            return;
        }
        CircuitElement* source = findElement(analysisParams[0]);
        if (source->getType() != "VoltageSource" && source->getType() != "CurrentSource") {
            std::cerr << "Error: " << analysisParams[0] << " is not a VoltageSource or CurrentSource. Cannot perform DC sweep on this component." << std::endl;
            return;
        }

        for (size_t i = 1; i < analysisParams.size(); ++i) {
            try {
                std::stod(analysisParams[i]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid numeric parameter for DC analysis: " << analysisParams[i] << ". " << e.what() << std::endl;
                return;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: DC analysis parameter out of range: " << analysisParams[i] << ". " << e.what() << std::endl;
                return;
            }
        }
    } else {
        std::cerr << "Error: Unsupported analysis type: " << analysisType << "." << std::endl;
        return;
    }

    std::cout << "Analysis Parameters: ";
    for (const auto& param : analysisParams) {
        std::cout << param << " ";
    }
    std::cout << std::endl;

    std::cout << "Variables to display:" << std::endl;
    for (const auto& var : variables) {
        if (isValidPrintVariable(var)) {
            std::cout << "  - " << var << " (Valid)" << std::endl;
        } else {

            std::cerr << "Error: One or more print variables are invalid. Cannot proceed with print command." << std::endl;
            std::cout << "--------------------" << std::endl;
            return;
        }
    }
    std::cout << "--------------------" << std::endl;
}