#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include "riscv.h"

using namespace std;

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

uint32_t instructionToMachineCode(const string& instruction){
    stringstream ss(instruction);
    string currWord;
    string operation;
    uint8_t opcode;
    string token;
    uint8_t rs0, rs1, rs2, rd;
    int16_t imm;
    vector<string> words;

    // convert current instruction into vector of words
    // remove leading whitespace
    getline(ss, token, ' ');
    words.push_back(token);
    //ss.ignore();

    while(getline(ss, token, ',')){
        ss.ignore();
        words.push_back(token);
    }

    // whats the opcode?
    operation = words[0];
    transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
    if(operation == "addi"){
        rd = stoi(words[1].substr(1, words[1].size() - 1)); //remove the leading x
        rs1 = stoi(words[2].substr(1, words[2].size() - 1)); //remove the leading x
        opcode = OP_IMM;
        imm = parseUImmediate(words[3]);
        return opcode | (rd << RD_OFFSET) | 
               (ADD_FUNCT3 << FUNCT3_OFFSET) | 
               (rs1 << RS1_OFFSET) | (imm << U_IMM_OFFSET);
    }
}

int testParseImmediate(){
    cout << parseUImmediate("#12") << endl;
    cout << parseUImmediate("#-1") << endl;
    cout << parseUImmediate("0x23") << endl;
    cout << parseUImmediate("#-5") << endl;

}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Please provide an assembly and output file" << endl;
        return 0;
    }
    string currentInstruction;
    uint32_t instructionIntOut;
    ifstream asmFile(argv[1], ifstream::in);
    ofstream machineFile(argv[2], ofstream::out);

    while(getline(asmFile, currentInstruction)){
        // TODO: write machine code to file
        instructionIntOut = instructionToMachineCode(currentInstruction);
        machineFile.write((char*)&instructionIntOut, sizeof(uint32_t));
    }
    return 0;
}

