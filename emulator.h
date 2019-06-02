#ifndef EMULATION_H
#define EMULATION_H

#include <cstdint>
#include <string>
#include <vector>

uint32_t registerNameToRegisterIndex(std::string registerName);

namespace emulation {

    const int REG_PRINT_COL_WIDTH = 4;

    enum equalities: uint8_t {
        equals,
        notEquals,
        greaterThan,
        lessThan,
        greaterThanOrEquals,
        lessThanOrEquals
    };

    struct CONDITION {
        // source value specification
        bool isPC;
        bool isRegister;
        uint32_t registerNumber;

        // condition 

        uint32_t targetValue;
    };
    

    class Emulator {
        private:
            uint32_t instructions_executed;
            uint32_t pc;
            uint8_t* program;
            std::vector<uint32_t> registers;
            
            void executeIType(uint32_t instruction);
            void executeRType(uint32_t instruction);
            void executeLUI(uint32_t instruction);
            void executeAUIPC(uint32_t instruction);
            void executeJALR(uint32_t instruction);
            void executeBranch(uint32_t instruction);
            bool areConditionsMet(std::vector<CONDITION>& conditions);
        public:
            Emulator(char* program, uint32_t initialPC);
            
            void step(bool inDebugMode);
            void stepMultiple(int steps, bool inDebugMode);
            void stepUntilConditionsMet(std::vector<CONDITION>& conditions, bool inDebugMode);
            void printInstructionsExecuted();
            void printPC();
            void printRegisters(bool useABINames, bool useDecimal);
            void printRegister(std::string registerName, bool useDecimal);
    };
}

#endif 
