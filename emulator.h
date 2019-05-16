#ifndef EMULATION_H
#define EMULATION_H

#include <cstdint>
#include <string>
#include <vector>

namespace emulation {

    const int REG_COUNT = 32;
    const int REG_PRINT_COL_WIDTH = 4;

    class Emulator {
        private:
            uint32_t pc;
            uint32_t* program;
            uint32_t instructions_executed;
            std::vector<uint32_t> registers;
            
            void printRegisterRow();
        public:
            Emulator(uint32_t* program, uint32_t initialPC);
            void step();
            void printInstructionsExecuted();
            void printRegisters(bool useABINames, bool useDecimal);
            void printRegister(std::string registerName, bool useDecimal);
    };
}

#endif 
