#include <string> 
#include <map>

#include "funBase.hpp"
#include "md5.hpp"

class md5StrFun : public funBase {
public:
  md5StrFun(){}
  virtual ~md5StrFun(){}
  virtual void init(stringMap& p){}
  virtual string operator() (string& s);
  
private:
  char *hex2Base64(const int key[4],char str[23]);
};
