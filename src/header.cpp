#include"include/header.h"
#include<fstream>
#include<iostream>

Header head;

void writeHeader(std::ofstream& out, const Header& header , const uint8_t freqTable = 256) {
    
    if(!out.is_open()){
        std::cout<<" FATAL ERROR : CAN NOT ACCESS INPUT STREAM TO WRITE HEADER \n";
        return;
    }

    out.clear();
    out.seekp(0);

    out.write("HFMN", 4);
    out.write(reinterpret_cast<const char*>(&header.originalSize), sizeof(uint64_t));
    out.write(reinterpret_cast<const char*>(&header.checksum), sizeof(uint64_t));
    out.write(reinterpret_cast<const char*>(header.freq), sizeof(uint64_t) * freqTable);

}

