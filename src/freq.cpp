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

        // Initialize header fields
        head.originalSize = 0;
        head.checksum = 0;
        for(int i=0; i<256; i++) {
            head.freq[i] = 0;
            freq[i] = 0; // also clear global freq just in case
        }

        uint8_t symbol; 
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

        if(in.tellg() != 0) std::cerr << "[FREQ] file pointer did not reset\n";
    }
