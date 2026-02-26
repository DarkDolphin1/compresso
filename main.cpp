#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include"compresso.h"

  void printUsage(){
    std::cout<<" Compresso : Usage  \n";
    std::cout<<" compresso [file]  \n";
    std::cout<<" calling with insufficient paremeters will show this message \n ";
  }

  int main(int argc , char** argv){
    std::string output;
    std::string input;
    if(argc > 2){
    input = argv[1];
      if(!std::filesystem::exists(input)){
			  std::cout<<"Given file does not exist , check the file name and try again \n";
			  std::exit(1);
      }
	output = argv[2];
    } else {
		std::cout<<"Provide a file to compress \n";
		printUsage();
		std::exit(1);
	}
	std::cout<<"Input  : "<<input<<"\n";
	std::cout<<"Output : "<<output<<"\n";

    compresso(input,output);

    return 0;
  }
