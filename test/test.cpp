// TODO : use multi-threading to speed things up
// TODO : improve memory usage
// TODO : add input validation to argv values passed , if invalid default to 0-255
#include"test.h"
#include<cstdint> 
#include<random>
#include<string>

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

    void write_random(std::ofstream &outstream , uint8_t start  , uint8_t end  ,
                      const size_t WRITE_LIMIT = 500ULL * 1024 * 1024 , const size_t CHUNK_SIZE = 1ULL * 1024 * 1024){

        if(!outstream.is_open()){
            std::cout<<"Error : failed to write test cases \n";
            return;
        }

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<uint8_t> dist(start, end); // Generate random data , in theory this should be harder to compress as we can't really find a strong pattern here

        std::vector<uint8_t> buffer(CHUNK_SIZE);

        size_t written = 0;
        while (written < WRITE_LIMIT) {
            size_t toWrite = std::min(CHUNK_SIZE, WRITE_LIMIT - written);

            for (size_t i = 0; i < toWrite; i++ ) buffer[i] = dist(rng);

            outstream.write(reinterpret_cast<char*>(buffer.data()), toWrite);
            written += toWrite;
        }
    }

    int main (int argc , char** argv){
        std::ofstream outLinear("linear.bin",std::ios::binary);
        std::ofstream outRandom("random.bin",std::ios::binary);

        size_t start = 0;
        size_t end = 255;

        if (argc == 3) {
            try {
                int s = std::stoi(argv[1]);
                int e = std::stoi(argv[2]);

                if (s < 0) s = 0;
                if (e > 255) e = 255;
                if (s > e) std::swap(s, e);

                start = static_cast<uint8_t>(s);
                end   = static_cast<uint8_t>(e);
            } catch (...) {
                std::cout << "Invalid input, defaulting to 0-255\n";
            }
        }
        std::cout<<"generating linear data ....\n";
        write_linear(outLinear);
        std::cout<<"generating random data ....\n";
        write_random(outRandom,start,end);
        std::cout<<" Test case generated ! \n";
        return 0;
    }