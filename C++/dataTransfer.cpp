#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <map>
#include <vector>
#include <memory>

#include "json.hpp"
#include "funFactory.hpp"

using namespace std;

/***************************************************************************
g++ -std=c++11 -m64 -o dataTransfer dataTransfer.cpp -ldl
****************************************************************************/
int main(int argc, char **argv) {
  vector<unique_ptr<colsTransform>> rowFs;
  map<string,unique_ptr<funFactory>> funFactorys;
  
  char* configFileName=argv[1];    
  ifstream inFile(configFileName);
  nlohmann::json jsonCfg;
  inFile >> jsonCfg;

  stringMap p;
  for (auto& funParas : jsonCfg) {
    for (auto& item : funParas.items()) {
      string name = item.key();      
      auto itemValue=item.value();
      string value;
      if (itemValue.is_number()) 
        value=to_string(itemValue);
      else
        value=itemValue;
      p[name]=value;
    }

    string soName=p["soName"];    
    auto it = funFactorys.find(p[soName]);
    if ( it == funFactorys.end() ) {
      funFactorys[soName]=unique_ptr<funFactory>(new funFactory(soName));
    }

    string createName=p["createName"];
    unique_ptr<funBase> pFun = unique_ptr<funBase>(funFactorys[soName]->create(createName));
 
    int nCol=stoi(p["colSeq"]);   
    
    pFun->init(p);

    rowFs.push_back(unique_ptr<colsTransform>(new colsTransform(nCol,move(pFun))));
    p.clear();
  }

  string row;
  vector<string> cols;  
  while (getline(cin, row)) {
    istringstream sin(row); 

    string col;
    while (getline(sin, col,',')) {
      cols.push_back(col);  
    }
    for (auto& r:rowFs) {  
      (*r)(cols);
    }
    cout << join(cols.begin(),cols.end(),",") <<endl;
    cols.clear();
  }

  rowFs.clear();
  funFactorys.clear();

  return 1 ;
}
