#include<iostream>
#include<string>
#include<fstream>
#include"compresso.h"

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

    // hard coding file names for now
    compresso("random.bin" , "comp_random.bin");

    return 0;
  }
