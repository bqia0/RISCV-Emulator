#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include "emulator.h"

using namespace std;
using namespace emulation;

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str);
  string tok;
 
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
 
  return internal;
}

bool hasInCommand(vector<string> stringVector, string target) {
    return find(stringVector.begin(), stringVector.end(), target) != stringVector.end();
}

uint32_t* readFileContents(char* filepath) {
    ifstream machineFile(filepath, ios::in|ios::binary|ios::ate);
    if (machineFile.is_open()) {

        // read file into memory
        streampos fileSize = machineFile.tellg();
        char* buffer = new char[fileSize];
        machineFile.seekg(0, ios::beg);
        machineFile.read(buffer, fileSize);
        machineFile.close();

        // cout << "File size: " << fileSize << endl;
        cout << "File Hex Dump:" << endl;
        for (int i = 0; i < fileSize; i++) {
            cout << setw(2) << setfill('0') << hex  << (0x000000FF & (unsigned int) buffer[i]) << " "; 
        }
        cout << endl;

        int programLength = fileSize / 4;
        uint32_t* program = new uint32_t[programLength];

        // rearrange into instruction format
        for(int i = 0; i < programLength; i++) {
            program[i] = ((0x000000FF & buffer[i * 4]) | 
               (0x000000FF & buffer[i * 4 + 1]) << 8 | 
               (0x000000FF & buffer[i * 4 + 2]) << 16 | 
               (0x000000FF & buffer[i * 4 + 3]) << 24);
            // cout << setw(8) << setfill('0') << hex << program[i] << endl;
        }

        delete[] buffer;

        return program;
    } else {
        throw invalid_argument("file could not be opened");
    }
}

void console(Emulator emulator) {
    string input;
    while (true) {
        cout << ">> ";
        getline(cin, input);
        std::vector<std::string> arrayTokens = split(input, ' ');

        if (arrayTokens.size() == 0) continue;
        string command = arrayTokens[0];

        // command handlers
        if (command == "r" || command == "regs") {
            emulator.printRegisters(hasInCommand(arrayTokens, "-abi"), hasInCommand(arrayTokens, "-10"));
        } else if (command == "reg") {
            if(arrayTokens.size() >= 2) {
                try {
                    emulator.printRegister(arrayTokens[1], hasInCommand(arrayTokens, "-10"));
                } catch (const invalid_argument& e) {
                    cout << "Specified register does not exist." << endl;
                }
            }
        } else if (command == "?") {
            cout << "Please see the README.md for help on using riscv-emulator." << endl;
        } else if (command == "quit" || command == "q") {
            break;
        } else {
            cout << "'" << input << "'" << " is not a command. Type '?' for help." << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please specify a machine code file." << endl;
        return 0;
    }

    try {
        uint32_t* program = readFileContents(argv[1]);
        Emulator emulator(program, 0);
        console(emulator);

        delete[] program;
    } catch (invalid_argument& e) {
        cout << "The specified file could not be opened";
        return 0;
    }

}
