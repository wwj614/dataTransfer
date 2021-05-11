#include "appendStr.hpp"
/****************************
 g++ -std=c++11 -m64 -fPIC -shared appendStr.cpp -o appendStr.so
*****************************/ 
extern "C" funBase* create() {
  return new appendStrFun();
}

