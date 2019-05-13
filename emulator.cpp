#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please specify a machine code file." << endl;
        return 0;
    }

    ifstream machineFile(argv[1], ios::in|ios::binary|ios::ate);
    if (machineFile.is_open()) {

        // read file into memory
        streampos fileSize = machineFile.tellg();
        char* fileContents = new char[fileSize];
        machineFile.seekg(0, ios::beg);
        machineFile.read(fileContents, fileSize);
        machineFile.close();

        cout << "File has been read into memory" << endl;

        // verification that its reading correctly?
        for (int i = 0; i < fileSize; i++) {
            // cout << fileContents[i] << ' ';
            cout << hex << setfill('0') << setw(2) << fileContents[i] << " ";
        }
        cout << endl;

        delete[] fileContents;
    } else {
        cout << "The specified file could not be opened." << endl;
    }
    return 0;
}
