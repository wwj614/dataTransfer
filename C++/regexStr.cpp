#include <string>
#include <regex>
#include <iterator>

#include "funBase.hpp"
#include "regexStr.hpp"
using namespace std;

/****************************
g++ -std=c++11 -m64 -fPIC -shared regexStr.cpp -o regexStr.so
*****************************/ 
extern "C" funBase* create() {
  return new regexStrFun();
}

void regexStrFun::init(stringMap& p) {
  _e=regex(p["P1"]);    
  _fmt=p["P2"];  
  _flags=regex_constants::format_first_only;
  if ( p["P3"] == "g" )
    _flags=regex_constants::match_any;  
};
  
string regexStrFun::operator() (string& s) {  
  return regex_replace (s,_e,_fmt,_flags);        
};

