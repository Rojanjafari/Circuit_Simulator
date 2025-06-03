#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <algorithm>
#include "Circuit.h"

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string trim(const string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return s;
    }
    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, (last - first + 1));
}

int main() {
    Circuit circuit;
    string line;

    cout << "Circuit Simulator - Type 'help' for commands or 'exit' to quit." << endl;

    while (true) {
        cout << "> ";
        getline(cin, line);
        line = trim(line);

        vector<string> parts = split(line, ' ');
        if (parts.empty() || trim(parts[0]).empty()) {
            continue;
        }

        string command = parts[0];
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "exit") {
            cout << "Exiting simulator." << endl;
            break;
        } else if (command == "help") {
            cout << "Available commands:" << endl;
            cout << "  add R<name> <node1> <node2> <value>    - Add a resistor (e.g., add R1 VIN GND 2.2k)" << endl;
            cout << "  add C<name> <node1> <node2> <value>    - Add a capacitor (e.g., add C1 VIN GND 1u)" << endl;
            cout << "  add L<name> <node1> <node2> <value>    - Add an inductor (e.g., add L1 VIN GND 1m)" << endl;
            cout << "  add GND <node>                       - Add a ground connection (e.g., add GND N001)" << endl;
            cout << "  delete R<name>                       - Delete a resistor (e.g., delete R1)" << endl;
            cout << "  delete C<name>                       - Delete a capacitor (e.g., delete C1)" << endl;
            cout << "  delete L<name>                       - Delete an inductor (e.g., delete L1)" << endl;
            cout << "  delete GND <node>                    - Delete a ground connection (e.g., delete GND N001)" << endl;
            cout << "  list                                 - List all circuit elements" << endl;
            cout << "  list R                               - List resistors" << endl;
            cout << "  list C                               - List capacitors" << endl;
            cout << "  list L                               - List inductors" << endl;
            cout << "  list GND                             - List ground connections" << endl;
            cout << "  nodes                                - List all available nodes" << endl;
            cout << "  rename node <old_name> <new_name>  - Rename a node (e.g., rename node N001 Vout)" << endl;
            cout << "  print <analysis_type> <analysis_params...> <variable1> <variable2>...  - Display output" << endl;
            cout << "    Examples:" << endl;
            cout << "      print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(n001) I(R1)" << endl;
            cout << "      print DC <SourceName> <StartVal> <EndVal> <Increment> V(out) I(C1)" << endl;
            cout << "  exit                                 - Exit the simulator" << endl;
        } else if (command == "add") {
            if (parts.size() < 2) {
                cerr << "Error: Insufficient arguments for 'add' command. Type 'help' for usage." << endl;
                continue;
            }
            string elementName = parts[1];
            char elementTypePrefix = toupper(elementName[0]);

            if (elementTypePrefix == 'R' && parts.size() == 5) {
                circuit.addResistor(elementName, parts[2], parts[3], parts[4]);
            } else if (elementTypePrefix == 'C' && parts.size() == 5) {
                circuit.addCapacitor(elementName, parts[2], parts[3], parts[4]);
            } else if (elementTypePrefix == 'L' && parts.size() == 5) {
                circuit.addInductor(elementName, parts[2], parts[3], parts[4]);
            } else if (elementName == "GND" && parts.size() == 3) {
                circuit.addGround(parts[2]);
            } else {
                cerr << "Error: Invalid 'add' command format or unsupported element type. Type 'help' for usage." << endl;
            }
        } else if (command == "delete") {
            if (parts.size() < 2) {
                cerr << "Error: Insufficient arguments for 'delete' command. Type 'help' for usage." << endl;
                continue;
            }
            string target = parts[1];
            if (target.length() < 1) {
                cerr << "Error: Invalid element name for delete command." << endl;
                continue;
            }

            char elementTypePrefix = toupper(target[0]);

            if (elementTypePrefix == 'R' || elementTypePrefix == 'C' || elementTypePrefix == 'L') {
                circuit.deleteElement(string(1, elementTypePrefix), target);
            } else if (target == "GND" && parts.size() == 3) {
                circuit.deleteElement("GND", parts[2]);
            }
            else {
                cerr << "Error: Invalid 'delete' command format or unsupported element type. Type 'help' for usage." << endl;
            }
        } else if (command == "list") {
            if (parts.size() == 1) {
                circuit.listAllElements();
            } else if (parts.size() == 2) {
                string type = parts[1];
                transform(type.begin(), type.end(), type.begin(), ::toupper);
                if (type == "R" || type == "RESISTOR") {
                    circuit.listElementsByType("Resistor");
                } else if (type == "C" || type == "CAPACITOR") {
                    circuit.listElementsByType("Capacitor");
                } else if (type == "L" || type == "INDUCTOR") {
                    circuit.listElementsByType("Inductor");
                } else if (type == "GND" || type == "GROUND") {
                    circuit.listElementsByType("Ground");
                } else {
                    cerr << "Error: Invalid element type for 'list' command. Use 'R', 'C', 'L', 'GND' or omit for all." << endl;
                }
            } else {
                cerr << "Error: Invalid 'list' command format. Type 'help' for usage." << endl;
            }
        } else if (command == "nodes") {
            if (parts.size() == 1) {
                circuit.listNodes();
            } else {
                cerr << "Error: 'nodes' command does not take arguments." << endl;
            }
        } else if (command == "rename") {
            if (parts.size() == 4 && parts[1] == "node") {
                circuit.renameNode(parts[2], parts[3]);
            } else {
                cerr << "ERROR: Invalid syntax correct format: rename node <old name> <new name>." << endl;
            }
        } else if (command == "print") {
            if (parts.size() < 3) {
                cerr << "Error: Insufficient arguments for 'print' command. Type 'help' for usage." << endl;
                continue;
            }
            string analysisType = parts[1];
            transform(analysisType.begin(), analysisType.end(), analysisType.begin(), ::toupper);

            size_t param_end_index = 0;
            if (analysisType == "TRAN") {
                if (parts.size() >= 4 && (parts[2].find('(') == string::npos && parts[3].find('(') == string::npos)) {
                    param_end_index = 3;
                    if (parts.size() >= 5 && parts[4].find('(') == string::npos) {
                        param_end_index = 4;
                        if (parts.size() >= 6 && parts[5].find('(') == string::npos) {
                            param_end_index = 5;
                        }
                    }
                }
            } else if (analysisType == "DC") {
                if (parts.size() >= 6 && (parts[2].find('(') == string::npos && parts[3].find('(') == string::npos &&
                                          parts[4].find('(') == string::npos && parts[5].find('(') == string::npos)) {
                    param_end_index = 5;
                }
            }

            if (param_end_index == 0) {
                cerr << "Error: Invalid 'print' command format or insufficient analysis parameters. Type 'help' for usage." << endl;
                continue;
            }

            vector<string> analysisParams;
            for (size_t i = 2; i <= param_end_index; ++i) {
                analysisParams.push_back(parts[i]);
            }

            vector<string> variables;
            for (size_t i = param_end_index + 1; i < parts.size(); ++i) {
                variables.push_back(parts[i]);
            }

            if (variables.empty()) {
                cerr << "Error: No variables specified for 'print' command. Type 'help' for usage." << endl;
                continue;
            }

            circuit.printOutput(analysisType, analysisParams, variables);
        } else {
            cerr << "Error: Unknown command '" << command << "'. Type 'help' for available commands." << endl;
        }
    }

    return 0;
}