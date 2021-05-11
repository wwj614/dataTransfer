#include <string>
#include <regex>
#include <codecvt>
#include <iterator>

#include "funBase.hpp"
#include "wregexStr.hpp"

using namespace std;
using convert_typeX = std::codecvt_utf8<wchar_t>;

/****************************
g++ -std=c++11 -m64 -fPIC -shared wregexStr.cpp -o wregexStr.so
*****************************/ 
extern "C" funBase* create() {
  return new wregexStrFun();
}

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
  wstring we=s2ws(p["P1"]);
  _e=wregex(we);  
  _fmt=s2ws(p["P2"]);  
  _flags=regex_constants::format_first_only;
  if ( p["P3"] == "g" )
    _flags=regex_constants::match_any;  
};
  
string wregexStrFun::operator() (string& s) {  
  wstring ws=s2ws(s);
  wstring r=regex_replace(ws,_e,_fmt,_flags);
  return ws2s(r);        
};

