#include <string>

#ifndef RISCV_H_
#define RISCV_H_

#define REG_COUNT 32
#define REG_INDEX_BITS 5

// Offsets when converting to machine code
#define OPCODE_WIDTH 7
#define RD_OFFSET 7
#define FUNCT3_OFFSET 12
#define RS1_OFFSET  15
#define RS2_OFFSET 20
#define FUNCT7_OFFSET 25
#define I_IMM_OFFSET 20
#define U_IMM_OFFSET  12
#define R_IMM_OFFSET 20
#define R_IMM_MASK 0x1F
#define S_IMM_OFFSET 7

// Opcodes
#define OP_IMM    0b0010011
#define OP_REG    0b0110011
#define OP_LOAD   0b0000011
#define OP_STORE  0b0100011
#define OP_JAL    0b1101111
#define OP_JALR   0b1100111
#define OP_BR     0b1100011
#define OP_LUI    0b0110111
#define OP_AUIPC  0b0010111

//Funct3
#define ADD_FUNCT3  0b000
#define AND_FUNCT3  0b111
#define OR_FUNCT3   0b110
#define XOR_FUNCT3  0b100
#define SLT_FUNCT3  0b010
#define SLTU_FUNCT3 0b011
#define SR_FUNCT3   0b101
#define SLL_FUNCT3  0b001

#define LB_FUNCT3   0b000
#define LW_FUNCT3   0b010
#define LH_FUNCT3   0b001
#define LBU_FUNCT3  0b100
#define LHU_FUNCT3  0b101

#define SW_FUNCT3  0b010
#define SH_FUNCT3  0b001
#define SB_FUNCT3  0b000

#define BEQ_FUNCT3  0b000
#define BNE_FUNCT3  0b001
#define BLT_FUNCT3  0b100
#define BGE_FUNCT3  0b101
#define BLTU_FUNCT3 0b110
#define BGEU_FUNCT3 0b111

const std::string abi_register_names[] = {
    "zero",
    "ra",
    "sp",
    "gp",
    "tp",
    "t0",
    "t1",
    "t2",
    "fp/s0",
    "s1",
    "a0",
    "a1",
    "a2",
    "a3",
    "a4",
    "a5",
    "a6",
    "a7",
    "s2",
    "s3",
    "s4",
    "s5",
    "s6",
    "s7",
    "s8",
    "s9",
    "s10",
    "s11",
    "t3",
    "t4",
    "t5",
    "t6"};

#endif