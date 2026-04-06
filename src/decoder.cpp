#include"heap.h"
#include"huffman.h"
#include"gencode.h"
#include"header.h"
#include"freq.h"

#include<fstream>
#include<string.h>
#include<filesystem>
#include<iostream>

// Forward declaration of verifyFormat to allow use in decode function
static bool verifyFormat(std::string source);

// Helper function to decode bitstream and write to output file
// unnecessary function overloading lol 
void decodeBits(std::ofstream &Dest , std::ifstream &Source ,Node* rootNode , Header &head){
    uint8_t byte;
    uint64_t written = 0;
    uint64_t OoriginalSize = head.originalSize;

    Node* current = rootNode;

    // Huffman decoding loop: traverse the tree bit by bit 
    while (Source.read(reinterpret_cast<char*>(&byte), 1) && written < OoriginalSize) {

        for (int i = 7; i >= 0; --i) {

            uint8_t bit = (byte >> i) & 1;

            if (bit == 0) current = current->left;
            else current = current->right;

            // at leaf node 
            if(current->left == nullptr && current->right == nullptr) {

                Dest.put(current->symbol);
                written++;

                // Ensure we don't write more than the original size (padding handling)
                if (written == OoriginalSize)
                    break;

                current = rootNode; // reset pointer to root for next symbol
            }
        }
    }
}

int decode(std::string input, std::string output){
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

    // Verify magic number "HFMN"
    if(verifyFormat(input)){
        std::cout<<"\n reading header from : "<<input<<"\n";
    } else return -3; // error while verifying header format or accessing file 


    // Ohead is nothing but an intermediate representation of the header , read from source and used as ref while writing 
    // Ohead = Ouput head(er)
    Header Ohead;

    // Skip the magic number as verifyFormat already checked it but we need to advance the stream
    char magic[4];
    Source.read(magic, 4);

    // Read the rest of the header
    Source.read(reinterpret_cast<char*>(&Ohead.originalSize), sizeof(Ohead.originalSize));
    Source.read(reinterpret_cast<char*>(&Ohead.checksum), sizeof(Ohead.checksum));
    Source.read(reinterpret_cast<char*>(Ohead.freq), sizeof(Ohead.freq));

    std::ofstream Dest(output, std::ios::binary);
    if(!Dest.is_open()){
        std::cout<<"error while writing to file \n";
        return -4; // error while writing
    }

    // Clear global freq and minHeap before rebuilding
    memset(freq, 0, sizeof(freq));
    while(!minHeap.empty()) minHeap.pop();

    // Copy freq table from header to global freq
    memcpy(freq, Ohead.freq, sizeof(freq));

    // Rebuild Heap and Huffman Tree
    buildHeap();
    const auto rootNode = buildTree();

    if (rootNode == nullptr) {
        std::cout << "Error: Huffman tree is empty\n";
        return -5;
    }

    // Perform the actual bit-by-bit decoding
    decodeBits(Dest, Source, rootNode, Ohead);
    
    // Cleanup
    destroyTree(rootNode);
    Dest.close();
    Source.close();

    std::cout << "Successfully decoded to: " << output << "\n";
    return 0;
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
