#include<fstream>
#include<cstdint>
#include<climits>
#include<iostream>


uint64_t freq[256] = {0}; 

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
