#ifndef CIRCUIT_SIMULATOR_PULSESOURCE_H
#define CIRCUIT_SIMULATOR_PULSESOURCE_H


#include "CircuitElement.h"
#include <string>
#include <vector>
#include <stdexcept>

class PulseSource : public CircuitElement {
public:
    enum class PulseType {
        STEP,
        SQUARE,
        TRIANGLE,



        UNDEFINED
    };

private:
    PulseType type;
    std::string typeString;
    std::vector<std::string> parameters;

public:
    PulseSource(const std::string& name, const std::string& node1, const std::string& node2,
                const std::string& typeStr, const std::vector<std::string>& params);

    void displayInfo() const override;
    std::string getType() const override;

    PulseType getPulseType() const;
    const std::string& getTypeString() const;
    const std::vector<std::string>& getParameters() const;

private:
    PulseType parsePulseType(const std::string& typeStr);
};


#endif 