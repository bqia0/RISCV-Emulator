# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = clang
CXXFLAGS = -lstdc++ -Wall -g 

# ****************************************************
# Targets needed to bring the executable up to date

assembler: assembler.o assembleInstructions.o 
	$(CXX) $(CXXFLAGS) -o assembler assembler.o assembleInstructions.o 

# The main.o target can be written more simply

assembler.o: assembler.cpp assembleInstructions.h riscv.h 
	$(CXX) $(CXXFLAGS) -c assembler.cpp

assembleInstructions.o: assembleInstructions.h riscv.h

