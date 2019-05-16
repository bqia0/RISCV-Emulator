#include "emulator.h"
#include "riscv.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace emulation;
using namespace std;

uint32_t getLSBMask(uint32_t numberOfBits) {
    if (numberOfBits < 32) {
        return ((uint32_t) 1 << numberOfBits) - 1;
    } else {
        return (uint32_t) 0xFFFFFFFF;
    }
}

Emulator::Emulator(char* program, uint32_t initialPC = 0) {
    this->program = (uint8_t*) program; // potential bug if char is not 8 bits?
    pc = initialPC;

    registers = vector<uint32_t>(REG_COUNT);
    instructions_executed = 0;
}

void Emulator::step() {

    // Decode logic
    uint32_t instruction = ((0x000000FF & program[pc]) | 
               (0x000000FF & program[pc + 1]) << 8 | 
               (0x000000FF & program[pc + 2]) << 16 | 
               (0x000000FF & program[pc + 3]) << 24);

    uint32_t opcode = instruction & getLSBMask(OPCODE_WIDTH); // bitmask will not work if OPCODE_WIDTH = 32;

    cout << setw(8) << setfill('0') << hex << pc;
    cout << ": " << setw(8) << setfill('0') << hex << instruction << " | ";
    if (opcode == OP_IMM) { // I-type instructions
        uint32_t funct3 = (instruction >> FUNCT3_OFFSET) & getLSBMask(3);
        int32_t immediate = ((int32_t) instruction >> I_IMM_OFFSET);
        uint32_t rs1 = (instruction >> RS1_OFFSET) & getLSBMask(REG_INDEX_BITS);
        uint32_t rd = (instruction >> RD_OFFSET) & getLSBMask(REG_INDEX_BITS);

        switch (funct3) {
            case ADD_FUNCT3:
                // TODO: check for rd == 0, x0 is hardwired to 0 according to ISA spec.
                registers[rd] = registers[rs1] + immediate;
                break;
            default:
                cout << "unrecognized I-type instruction";
        }
    }
    cout << endl;

    pc = pc + 4;
    instructions_executed++;
}

void Emulator::printInstructionsExecuted() {
    cout << instructions_executed << endl;
}

void Emulator::printRegisters(bool useABINames, bool useDecimal) {
    for (int i = 0; i < REG_COUNT; i++) {
        if (useABINames) {
            cout << setw(5) << setfill(' ') << right << abi_register_names[i];
        } else {
            cout << setw(5) << setfill(' ') << right << ("x" + to_string(i));
        }
        if (useDecimal) {
            cout << ": " << setw(10) << setfill(' ') << registers[i];
        } else { // TODO: Decide if we need to handle unsigned/signed
            cout << ": " << "0x" << setw(8) << setfill('0') << registers[i];
        }
        if ((i + 1) % REG_PRINT_COL_WIDTH == 0) {
            cout << endl;
        }
    }
}

void Emulator::printRegister(string registerName, bool useDecimal) {
    try {
        int registerNumber = -1;
        if (registerName[0] == 'x') {
            registerNumber = stoi(registerName.substr(1, registerName.size()));
        } else {
            for (int i = 0; i < REG_COUNT; i++) {
                if (registerName == abi_register_names[i]) registerNumber = i;
            }
            if (registerName == "fp" || registerName == "s0") registerNumber = 8;
        }
        if (registerNumber < 0 || registerNumber > REG_COUNT - 1) {
            throw invalid_argument("Specified register does not exist");
        }
        if (useDecimal) {
            cout << registers[registerNumber] << endl;
        } else {
            cout << "0x" << setw(8) << setfill('0') << registers[registerNumber] << endl;
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Specified register does not exist");
    }
}