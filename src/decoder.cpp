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
        std::cout<<"\n reading header from :"<<input;
    } else return -3; // error while verifying header format or accessing file 

    uint64_t originalSize;
    uint64_t checksum;
    uint64_t freq[256];

    Source.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));
    Source.read(reinterpret_cast<char*>(&checksum), sizeof(checksum));
    Source.read(reinterpret_cast<char*>(freq), sizeof(freq));

    std::ofstream *dest = mkoutfile("decompressed_file"); // generates the file with no data 
    if(dest == nullptr){
        std::cout<<"error while writing to file \n";
        return -4; // error while writing , mkoutfile returned null 
    }

    
    
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