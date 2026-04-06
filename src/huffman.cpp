#include"freq.h"
#include"heap.h"

    Node* buildTree(){
        if(minHeap.size() == 0) return nullptr;

        // Case: Only one unique symbol in the input
        // Standard Huffman requires at least two nodes to create an internal node
        // We add a dummy node to ensure the symbol gets at least a 1-bit code
        if (minHeap.size() == 1) {
            Node* leaf = minHeap.top();
            minHeap.pop();
            // Create a dummy node with 0 frequency and a symbol that won't appear (not used)
            Node* dummy = new Node{ 0, 0xFF, nullptr, nullptr };
            Node* parent = new Node{ leaf->freq, 0, leaf, dummy };
            minHeap.push(parent);
        }

            while (minHeap.size() > 1) {
                Node* left = minHeap.top();
                minHeap.pop();

                Node* right = minHeap.top();
                minHeap.pop();
                // Node format ( freq (Left freq + Right freq), symbol = 0 , left and right pointers );
                Node* parent = new Node{ left->freq + right->freq, 0, left, right };
                minHeap.push(parent);
            }
        Node* root = minHeap.top();
        minHeap.pop(); // Clear the root from minHeap
    return root;
    }

void destroyTree(Node* node) {
    if (!node) return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
