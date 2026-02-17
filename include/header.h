#pragma once

#include"include/freq.h"
#include<cstdint>


struct Header {
    uint64_t freq[256];       // 2048 bytes
    uint64_t originalSize;    // 8 bytes
    uint64_t checksum;        // 8 bytes
    char     magic[4];        // 4 bytes
};

// note : we do not write Header in this sequence , this sequence is supposed to avoid compiler paddings and the actual header format should look like this 

/*

char     magic[4];        // 4 bytes
uint64_t originalSize;    // 8 bytes
uint64_t checksum;        // 8 bytes
uint64_t freq[256];       // 2048 bytes

*/


