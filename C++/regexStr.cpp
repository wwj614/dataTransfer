#include <string>
#include <regex>
#include <codecvt>
#include <iterator>

#include "funBase.hpp"
#include "regexStr.hpp"
using namespace std;

/****************************
g++ -std=c++11 -m64 -fPIC -shared regexStr.cpp -o regexStr.so
*****************************/ 
extern "C" funBase* regexCreate() {
  return new regexStrFun();
}

extern "C" funBase* wregexCreate() {
  return new wregexStrFun();
}

void regexStrFun::init(stringMap& p) {
  _regexRule=regex(p["regexRule"]);    
  _result=p["result"];  
  _flags=regex_constants::format_first_only;
  if ( p["flags"] == "g" )
    _flags=regex_constants::match_any;  
};
  
string regexStrFun::operator() (string& s) {  
  return regex_replace (s,_regexRule,_result,_flags);        
};

using convert_typeX = std::codecvt_utf8<wchar_t>;

std::wstring s2ws(const std::string& str)
{
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(str);
}
 
std::string ws2s(const std::wstring& wstr)
{
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

void wregexStrFun::init(stringMap& p) {
  wstring regexRuleStr=s2ws(p["regexRule"]);
  _regexRule=wregex(regexRuleStr);  
  _result=s2ws(p["result"]);  
  _flags=regex_constants::format_first_only;
  if ( p["P3"] == "g" )
    _flags=regex_constants::match_any;  
};
  
string wregexStrFun::operator() (string& s) {  
  wstring ws=s2ws(s);
  wstring r=regex_replace(ws,_regexRule,_result,_flags);
  return ws2s(r);        
};

