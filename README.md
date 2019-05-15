# RiscV Emulator
- Assembler...WIP
- Emulator...basic framework created

## Usage

To use compile this project from source, clone this repository onto your local machine. You will need `clang`.

### Building and Using the Assembler
Use the make file and type the following command to invoke the makefile.
```
make
```

This will build the assembler into a file called `assemble`. You can use the assembler to generate a machine file from your RISC-V assembly file, which the emulator can use. In the same directory, call:
```
./assembler [assemblyFileLocation] [assemblyFileDestination]
```

### Building and Starting the Emulator
In the repository directory, type the following command to assembler the emulator.
```
clang++ -Wall -std=c++14 emulator.cpp main.cpp -o [desiredFileDestination]
```

With a machine file generated and the emulator compiled, you are now ready to begin emulation! You can begin using your emulator with the following command:
```
[emulatorFileLocation] [machineFileLocation]
```
Where `emulatorFileLocation` is the same as the `desiredFileDestination` from above.

### Emulator Commands
The emulator currently supports the following commands:

Command | Description
---|---
`r/regs (-abi) (-10)` | prints all registers, optionally with ABI labels, or in base 10.
`reg [registerName] (-10)` | prints the specified register, optionally in base 10. Accepts ABI or regular register names.
`q/quit` | quits the emulator.


