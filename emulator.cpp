#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdint>

using namespace std;

char* readFileContents(char* filepath) {
    ifstream machineFile(filepath, ios::in|ios::binary|ios::ate);
    if (machineFile.is_open()) {

        // read file into memory
        streampos fileSize = machineFile.tellg();
        char* buffer = new char[fileSize];
        machineFile.seekg(0, ios::beg);
        machineFile.read(buffer, fileSize);
        machineFile.close();

        cout << "File has been read into memory" << endl;

        // verification that its reading correctly?
        for (int i = 0; i < fileSize; i++) {
            cout << setw(2) << setfill('0') << hex << (int) buffer[i] << " "; 
        }
        cout << endl;
        return buffer;
    } else {
        throw invalid_argument("file could not be opened");
    }
}

void console() {
    string input;
    while(input != "q") {
        cout << ">> ";
        cin >> input;

        // TODO: implement some commands here
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please specify a machine code file." << endl;
        return 0;
    }

    try {
        char* fileContents = readFileContents(argv[1]);

        console();

        delete[] fileContents;
    } catch (invalid_argument& e) {
        cout << "The specified file could not be opened";
        return 0;
    }

}
