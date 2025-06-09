#ifndef CIRCUIT_SIMULATOR_CURRENTSOURCE_H
#define CIRCUIT_SIMULATOR_CURRENTSOURCE_H


#include "CircuitElement.h"
#include <string>
#include <stdexcept>

class CurrentSource : public CircuitElement {
private:
    double value;

public:
    CurrentSource(const std::string& name, const std::string& node1, const std::string& node2, double value);

    void displayInfo() const override;
    std::string getType() const override;

    double getValue() const;


    static double parseValue(const std::string& valueStr);
};


#endif
