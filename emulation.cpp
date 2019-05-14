#include "emulation.h"

using namespace emulation;

Emulator::Emulator() {
    registers[REG_COUNT] = { };
    pc = 0;
}