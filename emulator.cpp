#include "emulator.h"
#include "riscv.h"

using namespace emulation;

Emulator::Emulator(uint32_t* program, uint32_t initialPC = 0) {
    registers[REG_COUNT] = { };
    pc = initialPC;
    this->program = program;
}

void Emulator::step() {
    uint32_t instruction = program[pc];
    //decode();
}