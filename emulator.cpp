#include "emulator.h"
#include "riscv.h"
#include <iostream>

using namespace emulation;
using namespace std;

Emulator::Emulator(uint32_t* program, uint32_t initialPC = 0) {
    registers[REG_COUNT] = { };
    pc = initialPC;
    this->program = program;
}

void Emulator::step() {

    // Decode logic
    uint32_t instruction = program[pc];

}

void Emulator::printRegisters() {
    cout << "haha no registers" << endl;
}