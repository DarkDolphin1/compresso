#include<cstdint>
#include<fstream>
#include "include/readFile.h"

struct Node {
    uint8_t data;
    int freq;
    Node *left, *right;
    Node(uint8_t d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};



void readFile(std::string result , std::string path){

        std::ifstream in(path,std::ios::binary);

        if(!in.is_open()){
          std::cout<<"[ERROR] readFile: can not access input stream , is the file path valid ?";
          return;
        }

        std::string buffer("");
        
        while(std::getline(in,buffer)){
          result.append(buffer);
          buffer = "";
        }

        in.close();
    }
