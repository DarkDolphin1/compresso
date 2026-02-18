#include"freq.h"
#include"heap.h"
#include"gencode.h"
#include"encode.h"
#include"header.h"
#include"huffman.h"
#include"compresso.h"

#include<string.h>
#include<cstring>
#include<fstream>
#include<iostream>

void compresso(std::string input , std::string output){
    std::ifstream inBin (input,std::ios::binary);
    std::ofstream outBin (output,std::ios::binary);

    if(!inBin.is_open()){
        std::cout<<" FATAL : failed to access input file \n";
        return;
    }
    if(!outBin.is_open()){
        std::cout<<"FATAL : failed to make output file \n";
        return;
    }

    Header header;

    header.checksum = 0; // will be using CRC for checksum later 

    findFreq(inBin,freq,header); // copy freq table into header and also original size  

    // std::memcpy(header.freq, freq, sizeof(uint64_t) * 256); // why is this function provided with string library ??
    
    buildHeap();
    
    const auto rootNode = buildTree();
    
    generateCodes(rootNode,0,0);
    
    writeHeader(outBin,header); // decoder should parse this properly  

    encodeFile(inBin,outBin);
    
    destroyTree(rootNode);

}

/*
FLOW 
make a freq table first 

*/