#include"heap.h"
#include"huffman.h"
#include"gencode.h"
#include"header.h"

#include<fstream>
#include<string.h>
#include<filesystem>
#include<iostream>

std::ofstream* mkoutfile(std::string expName){
    std::ofstream outFile(expName,std::ios::binary);

    if(!outFile.is_open()){
        return nullptr;
    }

    return &outFile;
}

// unnecessary function overloading lol 
std::ofstream* mkoutfile(std::ofstream &Dest , std::ifstream &Source ,Node* rootNode , Header &head){
    uint8_t byte;
    uint64_t written = 0;
    uint64_t OoriginalSize = head.originalSize;

    Node* current = rootNode;

    while (Source.read(reinterpret_cast<char*>(&byte), 1) && written < OoriginalSize) {

        for (int i = 7; i >= 0; --i) {

            uint8_t bit = (byte >> i) & 1;

            if (bit == 0) current = current->left;
            else current = current->right;

            // at leaf node 
            if(current->left == nullptr && current->right == nullptr) {

                Dest.put(current->symbol);
                written++;

                if (written == OoriginalSize)
                    break;

                current = rootNode; // reset pointer 
            }
        }
    }

    return &Dest;
}

int decode(std::string input){
    std::ifstream Source (input,std::ios::binary);

    if(!Source.is_open()){
        if(!std::filesystem::exists(input)){
            std::cout<<"input file does not exists \n";
            std::cout<<"Verify that the file exists in the current directory \n";
            return -1; // file not found 
        } 
        else {
            std::cout<<"error while accessing file \n";
            return -2; // file exists but can not access
        }
    }

    if(verifyFormat(input)){
        std::cout<<"\n reading header from : "<<input<<"\n";
    } else return -3; // error while verifying header format or accessing file 


    // Ohead is nothing but an intermediate representation of the header , read from source and used as ref while writing 
    // Ohead = Ouput head(er)
    Header Ohead;

    Ohead.originalSize;
    Ohead.checksum;
    Ohead.freq[256];

    Source.read(reinterpret_cast<char*>(&Ohead.originalSize), sizeof(Ohead.originalSize));
    Source.read(reinterpret_cast<char*>(&Ohead.checksum), sizeof(Ohead.checksum));
    Source.read(reinterpret_cast<char*>(Ohead.freq), sizeof(Ohead.freq));

    std::ofstream *dest = mkoutfile("decompressed_file"); // generates the file with no data 
    if(dest == nullptr){
        std::cout<<"error while writing to file \n";
        return -4; // error while writing , mkoutfile returned null 
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> *minHeap = buildHeap(Ohead.freq); 

    const auto rootNode = buildTree(*minHeap);

    auto temp = mkoutfile(*dest,Source,rootNode,Ohead);
    
}


static bool verifyFormat(std::string source){ 
    // we need to verify first 4 bits so we can't rely on a pre-existing stream , or modify it . creating another one seems reasonable 

    std::ifstream Source(source,std::ios::binary);

    if(!Source.is_open()) return false;

    char magic[4];
    const char expected[4] = {'H','F','M','N'};

    Source.read(magic, 4);

    if (memcmp(magic, expected, 4) != 0) {
        std::cerr << "Invalid magic number\n";
        return false;
    }

    return true;
}