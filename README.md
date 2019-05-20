# RiscV Emulator
- Assembler...Basic instructions without labels or P-Ops
- Emulator...basic framework created

## Usage

To use compile this project from source, clone this repository onto your local machine. You will need `clang`.

### Building the Assembler and Emulator
Use the make file and type the following command to invoke the makefile.
```
make
```

### Using the Assembler
Assemble your assembly file to machine code by calling:
```
./assembler [assemblyFileLocation] [assemblyFileDestination]
```

### Starting the Emulator
With a machine file generated, you are now ready to begin emulation! You can begin using your emulator with the following command:
```
[emulatorFileLocation] [machineFileLocation]
```
Where `emulatorFileLocation` is the same as the `desiredFileDestination` from above.

### Emulator Commands
The emulator currently supports the following commands:

Command | Description
---|---
`c/count` | Prints how many instructions have been executed.
`pc` | Prints the current PC (PC of the next instruction to be executed).
`r/regs (-abi) (-10)` | Prints all registers, optionally with ABI labels, or in base 10.
`reg [registerName] (-10)` | Prints the specified register, optionally in base 10. Accepts ABI or regular register names.
`s/step (-d)` | Steps/executes the next instruction, optionally with additional details output to the console.
`s/step [numberOfSteps] (-d)` | Steps/executes the specified number of steps, optionally with additional details output to the console.
`q/quit` | Quits the emulator.
