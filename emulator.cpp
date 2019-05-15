#include "emulator.h"
#include "riscv.h"
#include <iostream>
#include <iomanip>

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

void Emulator::printRegisters(bool useABINames) {
    for (int i = 0; i < REG_COUNT; i++) {
        if (useABINames) {
            cout << setw(5) << setfill(' ') << right << abi_register_names[i];
        } else {
            cout << setw(5) << setfill(' ') << right << ("x" + to_string(i));
        }
        cout << ": " << "0x" << setw(8) << setfill('0') << registers[i];
        if ((i + 1) % REG_PRINT_COL_WIDTH == 0) {
            cout << endl;
        }
    }
}

void Emulator::printRegisterRow() {

}