#include "funBase.hpp"
using namespace std;

class mapStrFun : public funBase {
public:
  mapStrFun(){}
  virtual ~mapStrFun(){}
  virtual void init(stringMap& p);
  virtual string operator() (string& s);
  
private:
  keyPosMap _kps;
  stringVector _ks;
};
