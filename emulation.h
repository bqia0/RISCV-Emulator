#ifndef EMULATION_H
#define EMULATION_H

#include <cstdint>

namespace emulation {

    const int REG_COUNT = 32;

    class Emulator {
        private:
            uint32_t registers[];
            uint32_t pc;
            
        public:
            Emulator();
    };
}

#endif 
