#pragma once

#include<cstdint>


struct Node{
    uint64_t freq; 
    uint8_t symbol;
    Node* left;
    Node* right;
};

struct Compare {
    bool operator()(const Node* a, const Node* b) const;
};