#include "include/readFile.h"
#include<cstdint>

struct Node {
    uint8_t data;
    int freq;
    Node *left, *right;
    Node(uint8_t d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};



void readFile(std::string result , std::ifstream &in){
        std::string buffer("");
        
        if(!in.is_open()){
          std::cout<<"[ERROR] readFile: can not access input stream , is the file path valid ?";
          return;
        }

        while(std::getline(in,buffer)){
          result.append(buffer);
          buffer = "";
        }
    }
