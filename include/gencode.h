#pragma once
#include<cstdint>
#include"heap.h"

struct Code {
    uint64_t bits;          // The actual bits that we are assigning to a symbol. should have 64 zero's by default 
    uint8_t  length;        // length of code tell us how many bits are actually valid and should be used for symbol look up.
};

extern Code codes[256];

/*
We will recursively travel the binary tree and generate codes .
This is much like we are doing DFS , as only leaf nodes contain valid symbols.

DFS makes sure we reach all the leaf nodes without putting too much strain on the memory or CPU cycles 
The given function will recursively assign codes based on the binary tree and the path it took to reach the leaf node containing that symbol.
*/

void generateCodes(Node* node, uint64_t bits, uint8_t length);