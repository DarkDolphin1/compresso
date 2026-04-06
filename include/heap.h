#pragma once

#include<cstdint>
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

void buildHeap();

extern std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;