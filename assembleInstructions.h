#ifndef ASSEMBLE_INSTRUCTIONS_H
#define ASSEMBLE_INSTRUCTIONS_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Stores memory labels
extern unordered_map <string, uint32_t> labels;

// arithmetic
uint32_t registerArithmetic(const string & operation, const vector<string> &words);
uint32_t immediateArithmetic(const string & operation, const vector<string> &words);

// Jumps
uint32_t jal(const vector<string> &words);
uint32_t jalr(const vector<string> &words);

uint32_t lui(const vector<string> & words);
uint32_t auipc(const vector<string> & words);
uint32_t load(const string & operation, const vector<string> &words);
uint32_t store(const string & operation, const vector<string> &words);
uint32_t branch(const vector<string> &words);


int isLoad(const string & operation);
int isBranch(const string & operation);
int isRegisterArithmetic(const string & operation);
int isImmediateArithmetic(const string & operation);

// Immediate parsing
int32_t parseIImmediate(const string & imm);
int32_t parseUImmediate(const string & imm);
uint32_t parseSImmediate(const string & imm);
uint32_t parseBImmediate(const string & imm);
uint32_t parseJImmediate(const string & imm);

#define BV(n) (1 << (n))

#endif