#include "funBase.hpp"
using namespace std;
class appendStrFun : public funBase {
public:
  appendStrFun(){}
  virtual ~appendStrFun(){}
  virtual void init(stringMap& p) {
    _value=p["value"];
    _prefix=stoi(p["prefix"])>0;
  }
  virtual string operator() (string& s) {
    if (_prefix) return _value + s;  
    return s + _value;
  }
private:
  string _value; 
  bool _prefix;
};
