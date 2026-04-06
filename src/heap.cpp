#include<queue>
#include"heap.h"
#include"freq.h"


std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap; // will be using pointers to node instead of actual nodes 



bool Compare::operator()(const Node* a, const Node* b) const {
    if (a->freq != b->freq) {
        return a->freq > b->freq;
    }
    // Tie-breaker: use symbol value to ensure deterministic tree building
    return a->symbol > b->symbol;
}
;


    void buildHeap(){
        for(int i = 0; i < 256; i++){
            if(freq[i] > 0){
                Node *node = new Node { freq[i] , static_cast<uint8_t>(i) , nullptr , nullptr };

                minHeap.push(node);
            }
        }
    }
