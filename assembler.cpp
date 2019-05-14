#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include "riscv.h"

using namespace std;

string parseImmediate(const string imm){
    int32_t immediateInt;
    uint32_t immediateIntTwosComplement;
    if(imm.substr(0, 2) == "0x"){
        immediateInt = stoi(imm, NULL, 16);
        //cout << immediateInt << endl;
        return std::bitset<11>(immediateInt).to_string(); 
    }else if (imm[0] == '#'){
        immediateInt = stoi(imm.substr(1, imm.size() - 1));
        if(immediateInt < 0){
            //cout << immediateInt << endl;
            immediateIntTwosComplement = ~(immediateInt * -1) + 1;//~(immediateInt + 1);
            //cout << immediateIntTwosComplement << endl;
            return std::bitset<11>(immediateIntTwosComplement).to_string();
        }
        return std::bitset<11>(immediateInt).to_string();
    }
    return NULL; // error case
}

string instructionToMachineCode(const string& instruction){
    stringstream ss(instruction);
    string currWord;
    string operation;
    string opcode;
    string token;
    unsigned int rs0, rs1, rs2, rd;
    string imm;
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
        imm = parseImmediate(words[3]);
        return imm + bitset<3>(rs1).to_string() + ADD_FUNCT3 + bitset<3>(rd).to_string() + OP_IMM;
    }
}

int testParseImmediate(){
    cout << parseImmediate("#12") << endl;
    cout << parseImmediate("#-1") << endl;
    cout << parseImmediate("0x23") << endl;
    cout << parseImmediate("#-5") << endl;

}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Please provide an assembly and output file" << endl;
        return 0;
    }
    string currentInstruction;
    ifstream asmFile(argv[1], ifstream::in);
    ofstream machineFile(argv[2], ofstream::out);

    while(getline(asmFile, currentInstruction)){
        // TODO: write machine code to file
        machineFile << instructionToMachineCode(currentInstruction) << endl;
    }
    return 0;
}

