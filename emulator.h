#ifndef EMULATION_H
#define EMULATION_H

#include <cstdint>
#include <string>
#include <vector>

namespace emulation {

    const int REG_PRINT_COL_WIDTH = 4;

    class Emulator {
        private:
            uint32_t instructions_executed;
            uint32_t pc;
            uint8_t* program;
            std::vector<uint32_t> registers;
            
            void executeIType(uint32_t instruction);
            void executeRtype(uint32_t instruction);
        public:
            Emulator(char* program, uint32_t initialPC);
            void step(bool inDebugMode);
            void stepMultiple(int steps, bool inDebugMode);
            void printInstructionsExecuted();
            void printPC();
            void printRegisters(bool useABINames, bool useDecimal);
            void printRegister(std::string registerName, bool useDecimal);
    };
}

#endif 
