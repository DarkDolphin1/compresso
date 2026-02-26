#include<iostream>
#include<fstream>
#include<cstdint>
#include<climits>
#include<queue>

#include"header.h"
#include"freq.h"
#include"heap.h"

uint64_t freq[256] = {0};

    void findFreq(std::ifstream &in , uint64_t freq[] , Header &head){
        
        if(!in.is_open()){
            std::cerr<<"[FREQ] : Can not access file for reading \n";
            return;
        }

        uint8_t symbol; // a symbol is basically a set of bits ( here 8 bits ) , which is basically a byte. doing this to avoid bit manipulation shit
        uint64_t originalSize = 0;

        // make a frequency table 
        while (in.read(reinterpret_cast<char*>(&symbol), 1)) {
            freq[symbol]++;
            head.freq[symbol]++;
            originalSize++;
        }

        head.originalSize = originalSize;

        // reset file pointers 
        in.clear(); 
        in.seekg(0);

        if(in.peek() != 0) std::cerr<<"[FREQ] : file pointer probably did not reset \n ";

    }

