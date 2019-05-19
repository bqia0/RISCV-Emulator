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
    string token;
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
        return immediateArithmetic(operation, words); //TODO: refactor functions to only take word array
    }else if(operation == "lui"){
        return lui(words);
    }else if (operation == "auipc"){
        return auipc(words);
    }else if(isRegisterArithmetic(operation)){
        return registerArithmetic(operation, words);
    }else if(isLoad(operation)){
        return load(operation, words);
    }else if(operation == "sw" || operation == "sh" || operation == "sb"){
        return store(operation, words);
    }else if(isBranch(operation)){
        return branch(words);
    }else if(operation == "jal"){
        return jal(words);
    }else if(operation == "jalr"){
        return jalr(words);
    }else{
        cout << "BAD OPERATION: "<< operation << endl;
        exit(0);
    }
}

int isLabel(const string & instruction){
    size_t colonIndex;
    colonIndex = instruction.find(":");
    if(colonIndex!=string::npos){
        return true;
    }
    return false;
}

/*
 * Scans file for labels and adds them to an unordered_map 
 * defined in assembleInstructions.h
 * unordered_map maps label name to address of label (assuming first address is 0)
 */
void scanLabels(ifstream & asmFile){
    string currentInstruction;
    unsigned int instruction_counter = 0;
    while(getline(asmFile, currentInstruction)){
        if(isLabel(currentInstruction)){
            if(labels.find(currentInstruction) != labels.end()){
                cout << "Duplicate Label: " << currentInstruction << endl;
                exit(0);
            }else{
                labels[currentInstruction] = instruction_counter * 4;
            }
        }else{
             //labels don't count as instructions and therefore don't take memory
            instruction_counter++;
        }
    }
    asmFile.clear() ;
    asmFile.seekg(0, ios::beg) ;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Please provide an assembly and output file" << endl;
        return 0;
    }
    string currentInstruction;
    uint32_t instructionIntOut;
    uint32_t numInstructions = 0;
    ifstream asmFile(argv[1], ifstream::in);
    ofstream machineFile(argv[2], ofstream::out);
    scanLabels(asmFile);
    asmFile.seekg(0, ios::beg); //reset ifstream for actual instruction parsing
    while(getline(asmFile, currentInstruction)){
        instructionIntOut = instructionToMachineCode(currentInstruction);
        machineFile.write((char*)&instructionIntOut, sizeof(uint32_t));
        numInstructions++;
    }
    return 0;
}

