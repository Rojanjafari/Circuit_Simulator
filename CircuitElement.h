
#ifndef CIRCUIT_SIMULATOR_CIRCUITELEMENT_H
#define CIRCUIT_SIMULATOR_CIRCUITELEMENT_H

#include <string>
#include <vector>

class CircuitElement {
protected:
    std::string name;
    std::string node1;
    std::string node2;

public:
    CircuitElement(const std::string& name, const std::string& node1, const std::string& node2 = "");
    virtual ~CircuitElement() = default;

    const std::string& getName() const;
    const std::string& getNode1() const;
    const std::string& getNode2() const;


    virtual void displayInfo() const = 0;
    virtual std::string getType() const = 0;


    static std::string normalizeNodeName(const std::string& node);
};


#endif 