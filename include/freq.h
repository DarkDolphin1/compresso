#pragma once

#include<queue>
#include<cstdint>
#include<fstream>
#include<queue>

struct Header;

extern uint64_t freq[256];

void findFreq(std::ifstream &in,uint64_t[],Header &head);

