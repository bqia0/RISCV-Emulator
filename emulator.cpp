#include "emulator.h"
#include "riscv.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace emulation;
using namespace std;

Emulator::Emulator(uint32_t* program, uint32_t initialPC = 0) {
    registers = vector<uint32_t>(REG_COUNT);
    pc = initialPC;
    this->program = program;
}

void Emulator::step() {

    // Decode logic
    uint32_t instruction = program[pc];

}

void Emulator::printRegisters(bool useABINames, bool useDecimal) {
    for (int i = 0; i < REG_COUNT; i++) {
        if (useABINames) {
            cout << setw(5) << setfill(' ') << right << abi_register_names[i];
        } else {
            cout << setw(5) << setfill(' ') << right << ("x" + to_string(i));
        }
        if (useDecimal) {
            cout << ": " << setw(10) << setfill(' ') << registers[i];
        } else { // TODO: Decide if we need to handle unsigned/signed
            cout << ": " << "0x" << setw(8) << setfill('0') << registers[i];
        }
        if ((i + 1) % REG_PRINT_COL_WIDTH == 0) {
            cout << endl;
        }
    }
}

void Emulator::printRegister(string registerName, bool useDecimal) {
    try {
        int registerNumber = -1;
        if (registerName[0] == 'x') {
            registerNumber = stoi(registerName.substr(1, registerName.size()));
        } else {
            for (int i = 0; i < REG_COUNT; i++) {
                if (registerName == abi_register_names[i]) registerNumber = i;
            }
            if (registerName == "fp" || registerName == "s0") registerNumber = 8;
        }
        if (registerNumber < 0 || registerNumber > REG_COUNT - 1) {
            throw invalid_argument("Specified register does not exist");
        }
        if (useDecimal) {
            cout << registers[registerNumber] << endl;
        } else {
            cout << "0x" << setw(8) << setfill('0') << registers[registerNumber] << endl;
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Specified register does not exist");
    }
}