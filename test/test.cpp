// TODO : use multi-threading to speed things up
// TODO : improve memory usage
#include<test/test.h>
#include<cstdint> 
#include<random>


    void write_linear(std::ofstream &outstream , const size_t WRITE_LIMIT = 500ULL * 1024 * 1024 , const size_t CHUNK_SIZE = 1ULL * 1024 * 1024 ){
        if(!outstream.is_open()){
            std::cout<<"Error : failed to write test cases \n";
            return;
        }

        std::vector<u_int8_t> buffer(CHUNK_SIZE , 0x41);

        unsigned long int written = 0;
        while (written < WRITE_LIMIT) {
            unsigned long int toWrite = std::min(CHUNK_SIZE, WRITE_LIMIT - written);
            outstream.write(reinterpret_cast<char*>(buffer.data()), toWrite);
            written += toWrite;
        }
        // we will not be closing the output stream here , 
        // generally the lifetime of the object should be determined by the scope where it is created rather than a helper function 
    }

    void write_random(std::ofstream outstream , const size_t WRITE_LIMIT = 500ULL * 1024 * 1024 , const size_t CHUNK_SIZE = 1ULL * 1024 * 1024 ){
        if(!outstream.is_open()){
            std::cout<<"Error : failed to write test cases \n";
            return;
        }

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<uint8_t> dist(0, 255); // Generate random data , in theory this should be harder to compress as we can't really find a strong pattern here

        std::vector<uint8_t> buffer(CHUNK_SIZE);

        size_t written = 0;
        while (written < WRITE_LIMIT) {
            size_t toWrite = std::min(CHUNK_SIZE, WRITE_LIMIT - written);

            for (size_t i = 0; i < toWrite; i++ ) buffer[i] = dist(rng);

            outstream.write(reinterpret_cast<char*>(buffer.data()), toWrite);
            written += toWrite;
        }
    }