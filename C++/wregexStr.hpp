#include "funBase.hpp"
using namespace std;

#define REG_RULE "P1"
#define OUT_FORMAT "P2"
#define REQ_FLAG "P3"

class wregexStrFun : public funBase {
public:
  wregexStrFun(){}
  virtual ~wregexStrFun(){}
  virtual void init(stringMap& p);
  virtual string operator() (string& s);
  
private:
  wregex _e;
  wstring _fmt;
  regex_constants::match_flag_type _flags;
};
