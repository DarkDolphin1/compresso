#include<iostream>
#include<fstream>
#include<vector>
#include<cstdint>
#include<threads.h>

void write_linear(std::ofstream &outstream , const size_t WRITE_LIMIT = 500ULL * 1024 * 1024 , const size_t CHUNK_SIZE = 1ULL * 1024 * 1024 );

inline size_t getChunkSize(){
    const size_t MB = 1024 * 1024 * 1ULL;
    // get number of threads as input 
    // ideally each thread should get one chunk at a time 
    // one thread should know from where to right (starting poin) and how much to write(chunk size) 
    // implementation of multi-threading is really not a priority right now , so as for better memory management.
}