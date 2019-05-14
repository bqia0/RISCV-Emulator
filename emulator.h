#ifndef EMULATION_H
#define EMULATION_H

#include <cstdint>

namespace emulation {

    const int REG_COUNT = 32;

    class Emulator {
        private:
            uint32_t registers[];
            uint32_t pc;
            uint32_t* program;
            
        public:
            Emulator(uint32_t* program, uint32_t initialPC);
            void step();
    };
}

#endif 
