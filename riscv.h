#ifndef RISCV_H_
#define RISCV_H_

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

#endif