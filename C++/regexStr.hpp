#include "funBase.hpp"
using namespace std;

#define REG_RULE "P1"
#define OUT_FORMAT "P2"
#define REQ_FLAG "P3"

class regexStrFun : public funBase {
public:
  regexStrFun(){}
  virtual ~regexStrFun(){}
  virtual void init(stringMap& p);
  virtual string operator() (string& s);
  
private:
  regex _e;
  string _fmt;
  regex_constants::match_flag_type _flags;
};
