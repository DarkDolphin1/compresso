#include<iostream>
#include<string>
#include<fstream>
#include"include/readFile.h"

  void printUsage(){
    std::cout<<" Compresso : Usage  \n";
    std::cout<<" main [file] [message] \n";
    std::cout<<" calling with insufficient paremeters will show this message \n ";
    std::cout<<" THIS IS A TEST BRANCH AND DOES NOT RELATE TO FINAL INTENDED BEHAVIOUR \n";
  }
  int main(int argc , char** argv){
    
    if(argc < 3){
      std::cout<<"Not enough Arguments , see guide for more info \n";
      printUsage();
      std::exit(1);
    }


    const std::string path(argv[1]);
    std::string message(argv[2]);
    std::cout<<"File path is : "<<path<<"\n";

    std::ofstream outfile(path);
    if(!outfile.is_open()){
      std::cerr<<"Failed to open file: "<<path<<"\n";
      std::cout<<"File may not exist , check the path provided \n";
      std::exit(1);
    }
    outfile<<message;
    outfile.close();

    std::ifstream infile(path);
    if(!infile.is_open()){
      std::cout<<"Failed to read from the file: "<<path<<"\n";
      std::exit(1);
    }

    std::string content;
    infile>>content;
    std::cout<<"\n Test file content :"<<content<<std::endl;
    return 0;
  }

