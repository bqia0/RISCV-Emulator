#ifndef RISCV_H_
#define RISCV_H_

#define RD_OFFSET 11
#define FUNCT3_OFFSET RD_OFFSET + 3
#define RS1_OFFSET  FUNCT3_OFFSET + 3
#define RS2_OFFSET RS1_OFFSET + 3
#define FUNCT7_OFFSET RS2_OFFSET + 7
#define U_IMM_OFFSET RS1_OFFSET + 11

#define OP_IMM    0b0010011
#define OP_REG    0b0110011
#define OP_LOAD   0b0000011
#define OP_STORE  0b0100011
#define OP_JAL    0b1101111
#define OP_JALR   0b1100111
#define OP_BR     0b1100011

#define ADD_FUNCT3  0b000
#define AND_FUNCT3  0b111
#define OR_FUNCT3   0b110
#define XOR_FUNCT3  0b100
#define SLT_FUNCT3  0b010
#define SLTU_FUNCT3 0b011
#define SRA_FUNCT3  0b101
#define SRL_FUNCT3  0b101
#define SLL_FUNCT3  0b001


#endif