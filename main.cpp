#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> 
#include "Circuit.h"

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    Circuit circuit;
    string line;

    cout << "Circuit Simulator - Type 'help' for commands or 'exit' to quit." << endl;

    while (true) {
        cout << "> ";
        getline(cin, line);

        vector<string> parts = split(line, ' ');
        if (parts.empty()) {
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
            string elementName = parts[1];
            char elementTypePrefix = toupper(elementName[0]);

            if (elementTypePrefix == 'R') {
                circuit.deleteElement("R", elementName.substr(1));
            } else if (elementTypePrefix == 'C') {
                circuit.deleteElement("C", elementName.substr(1));
            } else if (elementTypePrefix == 'L') {
                circuit.deleteElement("L", elementName.substr(1));
            } else if (elementName == "GND" && parts.size() == 3) {
                circuit.deleteElement("GND", parts[2]);
            } else {
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
                cerr << "ERROR: Invalid syntax correct format: rename node <old name> <new name>[cite: 73]." << endl;
            }
        }
        else {
            cerr << "Error: Unknown command '" << command << "'. Type 'help' for available commands." << endl;
        }
    }

    return 0;
}