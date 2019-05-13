#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

string instructionToMachineCode(const string& instruction){
    stringstream ss(instruction);
    string currWord;
    string opcode;
    string token;
    vector<string> words;
    // convert current instruction into vector of words
    // remove leading whitespace
    getline(ss, token, ' ');
    words.push_back(token);
    ss.ignore();
    while(getline(ss, token, ',')){
        ss.ignore();
        words.push_back(token);
    }

    // whats the opcode?
    opcode = words[0];
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::tolower);
    return opcode;
}

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Please provide an assembly and output file" << endl;
        return 0;
    }
    string currentInstruction;
    ifstream asmFile(argv[1], ifstream::in);
    ofstream machineFile(argv[2], ofstream::out);

    while(getline(asmFile, currentInstruction)){
        // TODO: write machine code to file
        machineFile << instructionToMachineCode(currentInstruction);
    }
    return 0;
}

