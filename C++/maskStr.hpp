#include "funBase.hpp"
using namespace std;

class maskStrFun : public funBase {
public:
  maskStrFun(){}
  virtual ~maskStrFun();
  virtual void init(stringMap& p);
  virtual string operator() (string& s);
  
private:
  char* _maskFormat=nullptr;
  int _maskLen;
  char* _buf=nullptr;
  int _maxColLength;
};
