#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <map>
#include <vector>
#include <memory>

#include "json.hpp"
#include "csvReader.hpp"
#include "funFactory.hpp"

using namespace std;

/***************************************************************************
g++ -std=c++11 -m64 -o dataTransfer dataTransfer.cpp -ldl
****************************************************************************/
int main(int argc, char **argv) {
  char* configFileName=argv[1];    
  char delimited=argv[2][0];    

  vector<unique_ptr<colsTransform>> rowFs;
  map<string,unique_ptr<funFactory>> funFactorys;
  
  ifstream configFile(configFileName);
  nlohmann::json jsonCfg;
  configFile >> jsonCfg;
  stringMap p;
  for (auto& funParas : jsonCfg) {
    for (auto& item : funParas.items()) {
      string name = item.key();      
      auto itemValue=item.value();
      p[name]=itemValue.is_number()? to_string(itemValue) : itemValue.get<string>();
    }
    string soName=p["soName"];    
    auto it = funFactorys.find(p[soName]);
    if ( it == funFactorys.end() ) {
      funFactorys[soName]=unique_ptr<funFactory>(new funFactory(soName));
    }

    string createName=p["createName"];
    unique_ptr<funBase> pFun = unique_ptr<funBase>(funFactorys[soName]->create(createName));
    pFun->init(p);
 
    int nCol=stoi(p["colSeq"]);   
    rowFs.push_back(unique_ptr<colsTransform>(new colsTransform(nCol,move(pFun))));
    p.clear();
  }

  vector<string> cols;  
  CSVReader csv;
  csv.open("-");
  while(csv.nextCols(cols)) {
    for (auto& r:rowFs) {  
      (*r)(cols);
    }
    cout << join(cols.begin(),cols.end(),delimited) <<endl; 
    cols.clear();
  }

  rowFs.clear();
  funFactorys.clear();

  return 1 ;
}
