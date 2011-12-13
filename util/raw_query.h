#pragma once

#include <map>
#include <vector>
#include <string>

using namespace std;

class RawQuery
{
public:
  //
  RawQuery(const char* query_string);
  ~RawQuery();
  const char* get(const string& key) const;
protected:
  static char* decode(const char* str, int len, char* target);
  static int   is_hex(char c);
  //
  map<string, const char*> params_;
  vector<string>           keys_;
  char*                    buff_;
  unsigned int             size_;
};
