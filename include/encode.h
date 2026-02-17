#pragma once

#include"gencode.h"
#include<fstream>

void writeBit(std::ofstream&,uint8_t,uint8_t&,uint8_t&);

void writeCode(std::ofstream&,const Code&,uint8_t&,uint8_t&);

void encodeFile(std::ifstream&,std::ofstream& );

