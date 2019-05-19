#ifndef ASSEMBLE_INSTRUCTIONS_H
#define ASSEMBLE_INSTRUCTIONS_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

extern unordered_map <string, uint32_t> labels;
uint32_t immediateArithmetic(const string & operation, const vector<string> &words);
int isImmediateArithmetic(const string & operation);
int32_t parseIImmediate(const string & imm);
int32_t parseUImmediate(const string & imm);
uint32_t parseSImmediate(const string & imm);
uint32_t parseBImmediate(const string & imm);
uint32_t lui(const vector<string> & words);
uint32_t auipc(const vector<string> & words);
int isRegisterArithmetic(const string & operation);
uint32_t registerArithmetic(const string & operation, const vector<string> &words);
uint32_t load(const string & operation, const vector<string> &words);
uint32_t store(const string & operation, const vector<string> &words);
int isLoad(const string & operation);
int isBranch(const string & operation);
uint32_t branch(const vector<string> &words);


#endif