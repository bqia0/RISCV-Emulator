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
    rs2 = stoi(words[3].substr(1, words[3].size() - 1));
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

uint32_t load(const string & operation, const vector<string> &words){
    uint8_t rs1, rd, funct3, opcode;
    int16_t imm;
    size_t open_paren, close_paren;
    string rs1_string, imm_string;

    // Process source register and immediate
    string sourceRegAndImm = words[2];
    open_paren = sourceRegAndImm.find('(');
    close_paren = sourceRegAndImm.find(')');
    if(open_paren == string::npos || close_paren == string::npos){
        cout << "Bad Load Immediate " << endl; //TODO add more descriptive message
        exit(0);
    }
    imm_string = sourceRegAndImm.substr(0, open_paren);
    rs1_string = sourceRegAndImm.substr(open_paren + 2, close_paren - open_paren - 2); //-2 to skip the paren and the leading x

    if(imm_string.size() > 2 && imm_string.substr(0, 2) == "0x"){
        imm = stoi(imm_string, NULL, 16);
    }else{
        imm = stoi(imm_string, NULL, 10);
    }

    rs1 = stoi(rs1_string);

    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    opcode = OP_LOAD;
    funct3 = 0;

    if(operation == "lw"){
        funct3 = LW_FUNCT3;
    }else if (operation == "lb"){
        funct3 = LB_FUNCT3;
    }else if(operation == "lh"){
        funct3 = LH_FUNCT3;
    }else if(operation == "lbu"){
        funct3 = LBU_FUNCT3;
    }else if(operation == "lhu"){
        funct3 = LHU_FUNCT3;
    }else{
        cout << "Bad Load Instruction" << endl;
        exit(0);
    }
    uint32_t test = opcode | (rd << RD_OFFSET) | 
    (funct3 << FUNCT3_OFFSET) | 
    (rs1 << RS1_OFFSET) | (imm << I_IMM_OFFSET);  
    return test;
}

uint32_t store(const string & operation, const vector<string> &words){
    uint8_t rs1, rs2, funct3, opcode;
    uint32_t imm;
    size_t open_paren, close_paren;
    string rs1_string, imm_string;

    // Process source registers and immediate
    string sourceRegAndImm = words[2];
    open_paren = sourceRegAndImm.find('(');
    close_paren = sourceRegAndImm.find(')');
    if(open_paren == string::npos || close_paren == string::npos){
        cout << "Bad Load Immediate " << endl; //TODO add more descriptive message
        exit(0);
    }

    imm_string = sourceRegAndImm.substr(0, open_paren);
    rs1_string = sourceRegAndImm.substr(open_paren + 2, close_paren - open_paren - 2); //-2 to skip the paren and the leading x


    imm = parseSImmediate(imm_string);
    rs1 = stoi(rs1_string);
    rs2 = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    opcode = OP_STORE;
    funct3 = 0;

    if(operation == "sw"){
        funct3 = SW_FUNCT3;
    }else if (operation == "sh"){
        funct3 = SH_FUNCT3;
    }else if(operation == "sb"){
        funct3 = SB_FUNCT3;
    }else{
        cout << "Bad Store Instruction" << endl;
        exit(0);
    }
    uint32_t test =  opcode | imm | 
    (funct3 << FUNCT3_OFFSET) | (rs1 << RS1_OFFSET) |
    (rs2 << RS2_OFFSET);
    return test;
}

uint32_t branch(const vector<string> &words){
    uint8_t rs1, rs2, funct3, opcode;
    uint32_t imm;
    string immString;
    string operation; 
    operation = words[0];
    immString = words[3];
    imm = parseBImmediate(immString);
    rs1 = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    rs2 = stoi(words[2].substr(1, words[2].size() - 1)); 
    opcode = OP_BR;
    funct3 = 0;
    if(operation == "beq"){
        funct3 = BEQ_FUNCT3;
    }else if(operation == "bne"){
        funct3 = BNE_FUNCT3;
    }else if(operation == "blt"){
        funct3 = BLT_FUNCT3;
    }else if(operation == "bge"){
        funct3 = BGE_FUNCT3;
    }else if(operation == "bltu"){
        funct3 = BLTU_FUNCT3;
    }else if(operation == "bgeu"){
        funct3 = BGEU_FUNCT3;
    }else{
        cout << "Bad Branch Operation: " << words[0] << endl;
    }
    return opcode | imm | (funct3 << FUNCT3_OFFSET) |
    (rs1 << RS1_OFFSET) | (rs2 << RS2_OFFSET); 
}

uint32_t parseBImmediate(const string & imm){
    uint32_t fullImmediate;
    if(imm.size() > 2 && imm.substr(0, 2) == "0x"){
       fullImmediate = stoi(imm, NULL, 16);
    }else{
       fullImmediate = stoi(imm, NULL, 10);
    }
    return ((BV(11) & fullImmediate) >> 5) | ((fullImmediate & 0x1E) << 7) | ((fullImmediate & 0x7E0) << 20) | 
    ((BV(12) & fullImmediate) << 19);   
}

uint32_t parseJImmediate(const string & imm){
    uint32_t fullImmediate;
    if(imm.size() > 2 && imm.substr(0, 2) == "0x"){
       fullImmediate = stoi(imm, NULL, 16);
    }else{
       fullImmediate = stoi(imm, NULL, 10);
    }
    cout << imm << endl;
    uint32_t test = (fullImmediate & 0xFF000) | (fullImmediate & BV(11) << 9) | ((fullImmediate & 0x7FE) << 20) | 
    ((BV(20) & fullImmediate) << 11);   
    cout << test << endl;
    return test;
}

// S type immediate is bottom 12 bits with 13 bits in between
uint32_t parseSImmediate(const string & imm){
    uint32_t fullImmediate;
    if(imm.size() > 2 && imm.substr(0, 2) == "0x"){
       fullImmediate = stoi(imm, NULL, 16);
    }else{
       fullImmediate = stoi(imm, NULL, 10);
    }    
    return ((fullImmediate & 0x01F) << 7) | ((fullImmediate & 0xFE0) << 20);
}


int isLoad(const string & operation){
    if(operation == "lw" || operation == "lh" || 
    operation=="lb"|| operation == "lbu" || operation == "lhu"){
        return 1;
    }
    return 0;
}

int isBranch(const string & operation){
    if(operation == "beq" || operation == "bne" || operation == "blt" ||
       operation == "bge" || operation == "bltu" || operation == "bgeu"){
           return 1;
       }
    return 0;
}

uint32_t jal(const vector<string> &words){
    uint8_t rd, opcode;
    uint32_t imm;
    string immString;

    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    immString = words[2];
    imm = parseJImmediate(immString);
    opcode = OP_JAL;
    return opcode | (rd << RD_OFFSET) | imm;
}

uint32_t jalr(const vector<string> &words){
    uint8_t rd, rs1, opcode;
    uint32_t imm;
    string immString;

    rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
    rs1 = stoi(words[2].substr(1, words[2].size() - 1));
    immString = words[3];
    imm = parseIImmediate(immString);
    opcode = OP_JALR;

    return opcode | (rd << RD_OFFSET) | (0b000 << 12) | (rs1 << RS1_OFFSET)
    | (imm << I_IMM_OFFSET);
}