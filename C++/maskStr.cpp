#include <cstring>
#include <cassert>
#include <string>

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
  string maskFormat=p["maskFormat"];
  _maskLen=maskFormat.size();
  _maskFormat=new char[_maskLen+1];
  memcpy(_maskFormat,maskFormat.c_str(),_maskLen+1);

  _maxColLength=stoi(p["maxColLength"]);
  _buf=new char[_maxColLength];
};
  
string maskStrFun::operator() (string& s) {  
  int dataLen=s.size();
  assert(dataLen<_maxColLength);
  memcpy(_buf,s.c_str(),dataLen+1);
  int len=min(_maskLen,dataLen);
  for (int i=0;i<len;++i) {
    if (_maskFormat[i]=='*') {
      _buf[i]='*';
    }
  }
  return string(_buf);              
};

maskStrFun::~maskStrFun() { 
  if (_maskFormat) delete _maskFormat; 
  if (_buf)  delete _buf; 
};