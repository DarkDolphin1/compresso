#include<fstream>
#include<cstdint>
#include<climits>
#include<queue>
#include<iostream>
#include"include/freq.h"

    void findFreq(std::ifstream &in){
        
        if(!in.is_open()){
            std::cerr<<"[FREQ] : Can not access file for reading \n";
            return;
        }

        uint8_t symbol; // a symbol is basically a set of bits ( here 8 bits ) , which is basically a byte. doing this to avoid bit manipulation shit

        // make a frequency table 
        while (in.read(reinterpret_cast<char*>(&symbol), 1)) {
            freq[symbol]++;
        }

        // reset file pointers 
        in.clear(); 
        in.seekg(0);

        if(in.peek() != 0) std::cerr<<"[FREQ] : file pointer probably did not reset \n ";

    }

// building a heap tree

struct Node {
    uint64_t freq; 
    uint8_t symbol;
    Node* left;
    Node* right;
};

struct Compare {
    bool operator()(const Node* a, const Node* b) const {
        return (a->freq > b->freq);   // will be used later to build min-heap  
    }
};

std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap; // will be using pointers to node instead of actual nodes 

    void buildHeap(){
        for(int i = 0; i < 256; i++){
            if(freq[i] > 0){
                Node *node = new Node { freq[i] , static_cast<uint8_t>(i) , nullptr , nullptr };

                minHeap.push(node);
            }
        }
    }

