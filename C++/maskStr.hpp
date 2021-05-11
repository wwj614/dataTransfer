#include "funBase.hpp"
using namespace std;

class maskStrFun : public funBase {
public:
  maskStrFun(){}
  virtual ~maskStrFun(){ if (_mask) delete _mask; }
  virtual void init(stringMap& p);
  virtual string operator() (string& s);
  
private:
  char* _mask;
  int _maskLen;
};
