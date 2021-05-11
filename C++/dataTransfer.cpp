#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>

#include "funFactory.hpp"
using namespace std;

/***************************************************************************
g++ -std=c++11 -m64 -o dataTransfer dataTransfer.cpp -ldl
****************************************************************************/

int main(int argc, char **argv) {
  vector<unique_ptr<colsTransform>> rowFs;
  map<string,unique_ptr<funFactory>> funFactorys;
  
  char* fileName=argv[1]; //("dataTransfer.cfg");
  ifstream fcfg(fileName,ifstream::in);
  string row; 
  stringMap p;
  while (getline(fcfg, row)) {
    istringstream sin(row); 
    string col;
    char configDelimited='@';
    
    getline(sin, col,configDelimited);
    string soName=trim(col);
    auto it = funFactorys.find(soName);
    if ( it == funFactorys.end() ) {
      funFactorys[soName]=unique_ptr<funFactory>(new funFactory(soName));
    }
    
    getline(sin, col,configDelimited);
    string createName=trim(col);
    
    stringMap p;
    
    unique_ptr<funBase> pFun = unique_ptr<funBase>(funFactorys[soName]->create(createName));
    getline(sin, col,configDelimited);
    int nCol=stoi(trim(col));   
    
    int i=1;
    while (getline(sin, col,configDelimited)) {
      p["P"+to_string(i)]=trim(col);  
      i++;
    }
    pFun->init(p);
    rowFs.push_back(unique_ptr<colsTransform>(new colsTransform(nCol,move(pFun))));
    p.clear();
  }
  
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
