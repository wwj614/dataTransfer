#include <dlfcn.h>
using namespace std;

#include "funBase.hpp"

class funFactory {
public:
  funFactory(string& soName) {
    handler = dlopen(soName.c_str(), RTLD_NOW);
    if (! handler) {
      throw std::runtime_error(dlerror());
    }
  }

  funBase* create(string& createName) {
    dlerror();    //Reset_dlerror
    createFun_t creator = reinterpret_cast<createFun_t>(dlsym(handler, createName.c_str()));
    Check_dlerror();
    return creator();
  }

  ~funFactory() {
    if (handler) {
      dlclose(handler);
    }
  }

private:
  void* handler = nullptr;

  static void Check_dlerror() {
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
      throw std::runtime_error(dlsym_error);
    }
  }
};

class colsTransform {
public:
  colsTransform(int nCol, unique_ptr<funBase> transform) 
  : _nCol(nCol) { _transform=move(transform);
  }
  ~colsTransform() {}
  
  void operator () (stringVector& cols) {
	  if (_nCol >= cols.size()) return;  
    string s=cols[_nCol];
    if (!s.empty()) 
	    cols[_nCol]=(*_transform)(s);  
  }
  
//  void delFunBase() {
//    if (_transform) delete _transform;  
//  }
  
private:
  int _nCol; 
  unique_ptr<funBase> _transform;
};

template<class InputIterator>
string join (InputIterator first, InputIterator last, string delimited) {
  if (first==last) return "";
  string s = *(first++);
  while (first!=last) {
	s += (delimited + *first);  
    ++first;
  }
  return s;
}

string trim(string& str) {
  str.erase(0,str.find_first_not_of(" \t\r\n"));
  str.erase(str.find_last_not_of(" \t\r\n") + 1);
  return str;
}