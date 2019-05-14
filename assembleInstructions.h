#ifndef ASSEMBLE_INSTRUCTIONS_H
#define ASSEMBLE_INSTRUCTIONS_H

#include <string>
#include <vector>

using namespace std;

uint32_t immediateArithmetic(const string & operation, const vector<string> &words);
int isImmediateArithmetic(const string & operation);
int32_t parseIImmediate(const string & imm);
int32_t parseUImmediate(const string & imm);
uint32_t lui(const vector<string> & words);
uint32_t auipc(const vector<string> & words);

#endif