#include "funBase.hpp"
using namespace std;
class appendStrFun : public funBase {
public:
  appendStrFun(){}
  virtual ~appendStrFun(){}
  virtual void init(stringMap& p) {
    _s=p["P1"];
    _isHead=stoi(p["P2"])>0;
  }
  virtual string operator() (string& s) {
    if (_isHead) return _s + s;  
    return s + _s;
  }
private:
  string _s; 
  bool _isHead;
};
