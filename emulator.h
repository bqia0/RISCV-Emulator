#ifndef EMULATION_H
#define EMULATION_H

#include <cstdint>
#include <vector>

namespace emulation {

    const int REG_COUNT = 32;
    const int REG_PRINT_COL_WIDTH = 4;

    class Emulator {
        private:
            void printRegisterRow();

            uint32_t pc;
            uint32_t* program;
            std::vector<uint32_t> registers;
            
        public:
            Emulator(uint32_t* program, uint32_t initialPC);
            void step();
            void printRegisters(bool useABINames);
    };
}

#endif 
