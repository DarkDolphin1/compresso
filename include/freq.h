#pragma once

#include<queue>
#include<cstdint>
#include<fstream>
#include<queue>

struct Node{
    uint64_t freq; 
    uint8_t symbol;
    Node* left;
    Node* right;
};

struct Compare {
    bool operator()(const Node* a, const Node* b) const;
};

extern uint64_t freq[256] = {0}; 
void findFreq(std::ifstream);

extern std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;
