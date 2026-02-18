#include"freq.h"
#include"heap.h"
#include"gencode.h"
#include"encode.h"
#include"header.h"
#include"huffman.h"
#include"compresso.h"

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

    findFreq(inBin,freq,256);
    
    buildHeap();
    
    const auto rootNode = buildTree();
    
    generateCodes(rootNode,0,0);
    
    encodeFile(inBin,outBin);
    
    destroyTree(rootNode);
}

/*
FLOW 
make a freq table first 

*/