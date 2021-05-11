#ifndef FUNBASE_H
#define FUNBASE_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
typedef  map<string,string> stringMap;
typedef  unordered_map<string,int> keyPosMap;
typedef  vector<string> stringVector;

class funBase {
public:
  virtual ~funBase() {}
  virtual void init(stringMap& p) = 0;   //按参数名字传参数
  virtual string operator ()(string& str) = 0;
  };

typedef funBase *(*createFun_t)();

#endif // FUNBASE_H
