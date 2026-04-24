#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include"compresso.h"

void printUsage(){
    std::cout<<" Compresso : Usage  \n";
    std::cout<<" compresso [file] [output_file] \n";
    std::cout<<" compresso --decode [file] [output_file] \n";
    std::cout<<" calling with insufficient parameters will show this message \n";
}

int main(int argc , char** argv){
    std::string output;
    std::string input;
    bool isDecode = false;

    if (argc < 3) {
        printUsage();
        return 1;
    }

    if (std::string(argv[1]) == "--decode") {
        if (argc < 4) {
            std::cout << "Error: Provide input and output files for decoding\n";
            printUsage();
            return 1;
        }
        isDecode = true;
        input = argv[2];
        output = argv[3];
    } else {
        input = argv[1];
        output = argv[2];
    }

    if(!std::filesystem::exists(input) && !isDecode){
        std::cout<<"Given file does not exist: " << input << "\n";
        return 1;
    }

    std::cout<<"Input  : "<<input<<"\n";
    std::cout<<"Output : "<<output<<"\n";

    if (isDecode) {
        int res = decode(input, output);
        if (res != 0) {
            std::cout << "Decoding failed with error code: " << res << "\n";
            return 1;
        }
    } else {
        compresso(input, output);
    }

    return 0;
}
