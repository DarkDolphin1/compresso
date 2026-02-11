#include"include/gentree.h"
#include"include/heap.h"

Code codes[256] = {};

    void generateCodes(Node* node, uint64_t bits, uint8_t length){
        if (!node) return;

        // Leaf node
        if (node->left == nullptr && node->right == nullptr) {
            codes[node->symbol] = { bits, length };
            return;
        }

        // Traverse to left node (bit shift)
        generateCodes(node->left, bits << 1, length + 1);

        // i have tried to avoid bit manipulation magic but we will be needing it here
        // this is how we traverse to right side of binary tree
        generateCodes(node->right, (bits << 1) | 1, length + 1);
    }
