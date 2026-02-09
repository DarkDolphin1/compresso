#include<fstream>
#include<iostream>
#include<string>

#pragma once
// define the functions required to read files in a non-binary format 

    void readFile(std::string &content , std::ifstream &input); // reads the file from input and stores it in content

