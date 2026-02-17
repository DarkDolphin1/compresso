#include"include/encode.h"
#include"include/gencode.h"
#include<cstdint>
#include<fstream>
#include<iostream>


    void writeBit(std::ofstream& out, uint8_t bit, uint8_t& buffer, uint8_t& bitCount) {
        
        if(!out.is_open()){
            std::cout<<"[ERROR] writeBit : can not access output stream for writing \n";
            return;
        }

        buffer <<= 1;
        buffer |= bit;
        bitCount++;

        if (bitCount == 8) {
            out.put(static_cast<char>(buffer));
            buffer = 0;
            bitCount = 0;
        }
    }

    void writeCode(std::ofstream& out, const Code& code, uint8_t& buffer, uint8_t& bitCount) {
        if(!out.is_open()){
            std::cout<<"[ERROR] writeCode : can not access output stream for writing \n";
            return;
        }
        for (int i = code.length - 1; i >= 0; --i) {
            uint8_t bit = (code.bits >> i) & 1;
            writeBit(out, bit, buffer, bitCount);
        }
    }

    void encodeFile(std::ifstream& in, std::ofstream& out) {
        uint8_t buffer = 0;
        uint8_t bitCount = 0;

        uint8_t symbol;

        // check for cases where streams are not valid
        // normally an invalid input stream means we will never reach this stage during execution (the error case will be triggered way before) , we still check for it anyways

        if(!in.is_open()){
            std::cout<<"[ERROR] encode : can not access input stream for reading \n";
            return;
        }

        if(!out.is_open()){
            std::cout<<"[ERROR] encode : can not access output stream for writing \n";
            return;
        }

        while (in.read(reinterpret_cast<char*>(&symbol), 1)) {
            writeCode(out, codes[symbol], buffer, bitCount);
        }

        // Flush remaining bits
        if (bitCount > 0) {
            buffer <<= (8 - bitCount);
            out.put(static_cast<char>(buffer));
        }
    }
