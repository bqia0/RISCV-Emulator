#include <iostream>
#include "assembleInstructions.h"
#include "riscv.h"

uint32_t immediateArithmetic(const string & operation, const vector<string> &words){
    uint8_t rs0, rs1, rs2, rd, funct3, opcode;
    int16_t imm;
    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    rs1 = stoi(words[2].substr(1, words[2].size() - 1)); //remove the leading x
    opcode = OP_IMM;
    imm = parseUImmediate(words[3]);
    if(operation == "addi") {
        funct3 = ADD_FUNCT3;
    }else if(operation == "andi"){
        funct3 = AND_FUNCT3;
    }else if(operation == "ori"){
        funct3 = OR_FUNCT3;
    }else if(operation == "xori"){
        funct3 = XOR_FUNCT3;
    }else if(operation == "slti"){
        funct3 = SLT_FUNCT3;
    }else if(operation == "sltiu"){
        funct3 = SLTU_FUNCT3;
    }else if(operation == "srai"){
        funct3 = SRA_FUNCT3;
    }else if(operation == "srli"){
        funct3 = SRL_FUNCT3;
    }else if(operation == "slli"){
        funct3 = SLL_FUNCT3;
    }else{
        cout << "Bad Operation " << endl;
    }
    return opcode | (rd << RD_OFFSET) | 
    (funct3 << FUNCT3_OFFSET) | 
    (rs1 << RS1_OFFSET) | (imm << U_IMM_OFFSET);
}

int isImmediateArithmetic(const string & operation){
    if(operation == "addi"  ||
       operation == "andi"  ||
       operation == "ori"   ||
       operation == "xori"  ||
       operation == "slti"  ||
       operation == "sltiu" ||
       operation == "srai"  ||
       operation == "srli"  ||
       operation == "slli"){
           return 1;
       }
    return 0;
}

int32_t parseUImmediate(const string imm){
    if(imm.substr(0, 2) == "0x"){
       return stoi(imm, NULL, 16);
    }else if (imm[0] == '#'){
       return stoi(imm.substr(1, imm.size() - 1));
    }else{
        cout << "Invalid Immediate Type" << endl; //TODO Give a more descriptive message
        exit(0);
    }
}