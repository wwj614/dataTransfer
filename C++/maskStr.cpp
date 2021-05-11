#include <cstring>

#include "funBase.hpp"
#include "maskStr.hpp"
using namespace std;

/****************************
g++ -std=c++11 -m64 -fPIC -shared maskStr.cpp -o maskStr.so
*****************************/ 
extern "C" funBase* create() {
  return new maskStrFun();
}

void maskStrFun::init(stringMap& p) {
  string mask=p["P1"];
  _maskLen=mask.size();
  _mask=new char[_maskLen+1];
  memcpy(_mask,mask.c_str(),_maskLen+1);
};
  
string maskStrFun::operator() (string& s) {  
  int dataLen=s.size();
  char* data=new char[dataLen+1];
  memcpy(data,s.c_str(),dataLen+1);
  int len=min(_maskLen,dataLen);
  for (int i=0;i<len;++i) {
    if (_mask[i]=='*') {
      data[i]='*';
    }
  }
  return string(data);              
};
  
