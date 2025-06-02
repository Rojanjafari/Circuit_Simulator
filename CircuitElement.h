//
// Created by ASUS on 6/3/2025.
//

#ifndef CIRCUIT_SIMULATOR_CIRCUITELEMENT_H
#define CIRCUIT_SIMULATOR_CIRCUITELEMENT_H

#include <string>
#include <vector>

using namespace std;

class CircuitElement {
protected:
    string name;
    string node1;
    string node2;

public:
    CircuitElement(const string& name, const string& node1, const string& node2 = "");
    virtual ~CircuitElement() = default;

    const string& getName() const;
    const string& getNode1() const;
    const string& getNode2() const;

    virtual void displayInfo() const = 0;
    virtual string getType() const = 0;

    static string normalizeNodeName(const string& node);
};


#endif //CIRCUIT_SIMULATOR_CIRCUITELEMENT_H