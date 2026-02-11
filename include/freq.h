#pragma once

#include<queue>
#include<cstdint>
#include<fstream>
#include<queue>


extern uint64_t freq[256] = {0}; 
void findFreq(std::ifstream);

extern std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;
