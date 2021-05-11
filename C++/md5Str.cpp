#include "funBase.hpp"
#include "md5Str.hpp"
/****************************
g++ -std=c++11 -m64 -fPIC -shared md5Str.cpp md5.cpp -o md5Str.so
*****************************/ 
extern "C" funBase* create() {
  return new md5StrFun();  
}

string md5StrFun::operator() (string& s) {
  const char * ps=s.c_str();
  int md5Code[4];
  MD5Data((const unsigned char*)ps,s.length(),(char *)md5Code);
  char md5CodeStr[23];
  return string(hex2Base64(md5Code,md5CodeStr));
};
  
char* md5StrFun::hex2Base64(const int key[4],char str[23]) {
  static const char b[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz[]";   
  int i;
  unsigned int t;
  unsigned char *k=(unsigned char *)key;
  char *p=str;
  for (i=0;i<5;i++) {
    t=k[i+i+i]|(k[i+i+i+1]<<8)|(k[i+i+i+2]<<16);
    *p=b[t&0x0000003F]; p++;
    *p=b[(t>>6)&0x0000003F]; p++;
    *p=b[(t>>12)&0x0000003F]; p++;
    *p=b[t>>18]; p++;
  }
  *p=b[k[15]&0x0F]; p++;
  *p=b[k[15]>>4]; p++;
  *p='\0';
  return str;
};
