#include "include/readFile.h"

    void readFile(std::string result , std::ifstream &in){
        std::string buffer("");
        
        if(!in.is_open()){
          std::cout<<"[ERROR] readFile: can not access input stream , is the file path valid ?"
          return;
        }

        while(std::getline(in,buffer)){
          result.append(buffer);
          buffer = "";
        }
    }

    void writeFile(const std::string &message , std::ofstream &out){
      // keeping this empty for now because writing to a file in binary needs some bit-manipulation magic 
      return;
    }
