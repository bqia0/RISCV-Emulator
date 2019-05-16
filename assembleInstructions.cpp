#include <iostream>
#include "assembleInstructions.h"
#include "riscv.h"
#include <bitset>

unordered_map <string, uint32_t> labels;

uint32_t immediateArithmetic(const string & operation, const vector<string> &words){
    uint8_t rs1, rd, funct3, opcode, funct7;
    int16_t imm;
    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    rs1 = stoi(words[2].substr(1, words[2].size() - 1)); //remove the leading x
    opcode = OP_IMM;
    funct3 = 0;
    funct7 = 0;
    imm = parseIImmediate(words[3]);
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
        funct7 = 0b0100000;
        funct3 = SR_FUNCT3;
    }else if(operation == "srli"){
        funct7 = 0;
        funct3 = SR_FUNCT3;
    }else if(operation == "slli"){
        funct7 = 0;
        funct3 = SLL_FUNCT3;
    }else{
        cout << "Bad Operation " << endl;
    }

    if(operation == "srai" || operation == "srli" || operation == "slli"){
        return opcode | (rd << RD_OFFSET) | 
        (funct3 << FUNCT3_OFFSET) | 
        (rs1 << RS1_OFFSET) | ((imm & R_IMM_MASK) << R_IMM_OFFSET) |
        (funct7 << FUNCT7_OFFSET);
    }

    return opcode | (rd << RD_OFFSET) | 
    (funct3 << FUNCT3_OFFSET) | 
    (rs1 << RS1_OFFSET) | (imm << I_IMM_OFFSET);
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

uint32_t registerArithmetic(const string & operation, const vector<string> &words){
    uint8_t rs1, rs2, rd, funct3, opcode, funct7;
    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    rs1 = stoi(words[2].substr(1, words[2].size() - 1)); //remove the leading x
    rs2 = stoi(words[3].substr(1, words[2].size() - 1));
    opcode = OP_REG;
    funct3 = 0;
    funct7 = 0;
    if(operation == "add") {
        funct3 = ADD_FUNCT3;
    }else if(operation == "sub"){
        funct3 = ADD_FUNCT3;
        funct7 = 0b0100000;
    }else if(operation == "and"){
        funct3 = AND_FUNCT3;
    }else if(operation == "or"){
        funct3 = OR_FUNCT3;
    }else if(operation == "xor"){
        funct3 = XOR_FUNCT3;
    }else if(operation == "slt"){
        funct3 = SLT_FUNCT3;
    }else if(operation == "sltu"){
        funct3 = SLTU_FUNCT3;
    }else if(operation == "sra"){
        funct3 = SR_FUNCT3;
        funct7 = 0b0100000;
    }else if(operation == "srl"){
        funct3 = SR_FUNCT3;
    }else if(operation == "sll"){
        funct3 = SLL_FUNCT3;
    }else{
        cout << "Bad Operation " << endl;
    }
    uint32_t test = opcode | (rd << RD_OFFSET) | 
    (funct3 << FUNCT3_OFFSET) | 
    (rs1 << RS1_OFFSET) | (rs2 << RS2_OFFSET) |
    (funct7 << FUNCT7_OFFSET);
    // bitset<32> a(test);
    // cout << a.to_string() << endl;
    return test;
}


int isRegisterArithmetic(const string & operation){
    if(operation == "add"  ||
       operation == "sub"  ||
       operation == "and"  ||
       operation == "or"   ||
       operation == "xor"  ||
       operation == "slt"  ||
       operation == "sltu" ||
       operation == "sra"  ||
       operation == "srl"  ||
       operation == "sll"){
           return 1;
       }
    return 0;   
}

uint32_t lui(const vector<string> & words){
    uint8_t opcode;
    uint8_t rd;
    int32_t imm;
    imm = parseUImmediate(words[2]);
    opcode = OP_LUI;
    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    return opcode | (rd << RD_OFFSET) | (imm << U_IMM_OFFSET);
}

uint32_t auipc(const vector<string> & words){
    uint8_t opcode;
    uint8_t rd;
    int32_t imm;
    imm = parseUImmediate(words[2]);
    opcode = OP_AUIPC;
    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    return opcode | (rd << RD_OFFSET) | (imm << U_IMM_OFFSET);
}

int32_t parseIImmediate(const string & imm){
    if(imm.substr(0, 2) == "0x"){
       return stoi(imm, NULL, 16);
    }else if (imm[0] == '#'){
       return stoi(imm.substr(1, imm.size() - 1));
    }else{
        cout << "Invalid Immediate Type" << endl; //TODO Give a more descriptive message
        exit(0);
    }
}

int32_t parseUImmediate(const string & imm){
    if(imm.substr(0, 2) == "0x"){
       return stoi(imm, NULL, 16);
    }else if (imm[0] == '#'){
       return stoi(imm.substr(1, imm.size() - 1));
    }else{
        cout << "Invalid Immediate Type" << endl; //TODO Give a more descriptive message
        exit(0);
    }    
}

// TODO: Actual support for proper loads and stores

// uint32_t load(const string & operation, const vector<string> &words){
//     uint8_t rs1, rd, funct3, opcode, funct7;
//     int16_t imm;
//     rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
//     rs1 = stoi(words[2].substr(1, words[2].size() - 1)); //remove the leading x
//     opcode = OP_LOAD;
//     funct3 = 0;
//     imm = parseIImmediate(words[3]);

//     if(operation == "lw"){
//         funct3 = LW_FUNCT3;
//     }else if (operation == "lb"){
//         funct3 = LB_FUNCT3;
//     }else if(operation == "lh"){
//         funct3 = LH_FUNCT3;
//     }else if(operation == "lbu"){
//         funct3 = LBU_FUNCT3;
//     }else if(operation == "lhu"){
//         funct3 = LHU_FUNCT3;
//     }else{
//         cout << "Bad Load Instruction" << endl;
//         exit(0);
//     }
//     return opcode | (rd << RD_OFFSET) | 
//     (funct3 << FUNCT3_OFFSET) | 
//     (rs1 << RS1_OFFSET) | (imm << I_IMM_OFFSET);    
// }

// uint32_t store(const string & operation, const vector<string> &words){
//     uint8_t rs1, rd, funct3, opcode, funct7;
//     int16_t imm;
//     rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
//     rs1 = stoi(words[2].substr(1, words[2].size() - 1)); //remove the leading x
//     opcode = OP_LOAD;
//     funct3 = 0;
//     if(operation == "sw"){
//         funct3 = SW_FUNCT3;
//     }else if (operation == "sh"){
//         funct3 = SH_FUNCT3;
//     }else if(operation == "sb"){
//         funct3 = SB_FUNCT3;
//     }else{
//         cout << "Bad Store Instruction" << endl;
//         exit(0);
//     }
//     return opcode | 
// }

// // S type immediate is bottom 12 bits with 13 bits in between
// int32_t parseSImmediate(const string & imm){
//     int32_t fullImmediate;
//     if(imm.substr(0, 2) == "0x"){
//        fullImmediate = stoi(imm, NULL, 16);
//     }else if (imm[0] == '#'){
//        fullImmediate = stoi(imm.substr(1, imm.size() - 1));
//     }else{
//         cout << "Invalid Store Immediate Type" << endl; //TODO Give a more descriptive message
//         exit(0);
//     }    
//     return (fullImmediate & 0x1F) | ((fullImmediate & 0xFE0) << 25);
// }