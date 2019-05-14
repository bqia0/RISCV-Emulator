#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "riscv.h"
#include "assembler.h"
#include "assembleInstructions.h"

using namespace std;

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
    getline(ss, token, ' ');
    words.push_back(token);
    while(getline(ss, token, ',')){
        ss.ignore();
        words.push_back(token);
    }

    operation = words[0];
    transform(operation.begin(), operation.end(), operation.begin(), ::tolower);

    if(isImmediateArithmetic(operation)){
        return immediateArithmetic(operation, words);
    }else if(operation == "lui"){
        return lui(words);
    }
    //TODO: REST OF OPCODES
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

