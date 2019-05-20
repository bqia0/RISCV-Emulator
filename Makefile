# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = clang
CXXFLAGS = -lstdc++ -Wall -g 

# ****************************************************
# Targets needed to bring the executable up to date

all: assembler emulator

assembler: assembler.o assembleInstructions.o 
	$(CXX) $(CXXFLAGS) -o assembler assembler.o assembleInstructions.o 

emulator: main.o emulator.o
	$(CXX) $(CXXFLAGS) -o emulator main.o emulator.o 
# The main.o target can be written more simply

assembler.o: assembler.cpp assembleInstructions.h riscv.h 
	$(CXX) $(CXXFLAGS) -c assembler.cpp

assembleInstructions.o: assembleInstructions.h riscv.h

emulator.o: emulator.cpp riscv.h
	$(CXX) $(CXXFLAGS) -c emulator.cpp

main.o: main.cpp emulator.h
	$(CXX) $(CXXFLAGS) -c main.cpp
