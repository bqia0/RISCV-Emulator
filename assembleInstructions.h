#ifndef ASSEMBLE_INSTRUCTIONS_H
#define ASSEMBLE_INSTRUCTIONS_H

#include <string>
#include <vector>

using namespace std;

uint32_t immediateArithmetic(const string & operation, const vector<string> &words);
int isImmediateArithmetic(const string & operation);
int32_t parseUImmediate(const string imm);

#endif