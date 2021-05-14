#include <fstream>
#include <sstream>

#include "funBase.hpp"
#include "mapStr.hpp"
using namespace std;

/****************************
g++ -std=c++11 -m64 -fPIC -shared mapStr.cpp -o mapStr.so
*****************************/ 
extern "C" funBase* create() {
  return new mapStrFun();
}

void mapStrFun::init(stringMap& p) {
  ifstream fin(p["mapFile"].c_str()); 
  int n=stoi(p["keyCount"]);  
  _kps.rehash(n); 
  _ks.reserve(n); 
  
  string row; 
  while (getline(fin, row)) {
    istringstream sin(row); 
    string key;
    string indexStr;
    getline(sin, key, ',');
    getline(sin, indexStr, ',');    //取前两列
    _kps[key]=stoi(indexStr);
    _ks.push_back(key);
  }
};
  
string mapStrFun::operator() (string& s) {  
  keyPosMap::const_iterator it = _kps.find(s);
  if ( it == _kps.end() ) return s;
  return _ks[it->second];              
};
  
