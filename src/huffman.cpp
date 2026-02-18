#include"freq.h"
#include"heap.h"

    Node* buildTree(){
        if(minHeap.size() == 0) return nullptr;

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
    return root;
    }

void destroyTree(Node* node) {
    if (!node) return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
