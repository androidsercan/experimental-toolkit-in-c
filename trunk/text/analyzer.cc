// $Id: analyzer.cc 4299 2011-09-26 08:16:24Z haowu $

#include "analyzer.h"

//
//
// public
//
//

Analyzer::Analyzer()
{
  //
}

Analyzer::Analyzer(const string& sw_file)
{
  ifstream ifs(sw_file.c_str());
  string line;
  while (getline(ifs, line)) {
    line = Util::Trim(line);
    if (line == "") {
      continue;
    }
    s_sw_.insert(line);
  }
  ifs.close();
}

void Analyzer::Tokenize(const string& str, vector<string>* z_word) const
{
  char buff[0x100];
  const char* p = str.c_str();
  while (*p) {
    p = Tokenize(p, buff);
    string word = buff;
    int len = word.length();
    if (len <= MAX_KEYWORD_LENGTH &&
        s_sw_.find(word) == s_sw_.end()) {
      z_word->push_back(word);
    }
  }
}

//
//
// protected
//
//

bool Analyzer::IsValidCharacter(char c) const
{
  return /* c == '-' || */ (c >= 0 && isalnum(c));
}

const char* Analyzer::Tokenize(const char* in, char* out) const
{
  while (*in && !IsValidCharacter(*in))
    in++;
  while (IsValidCharacter(*in)) {
    *out = tolower(*in);
    out++;
    in++;
  }
  *out = 0;
  while (*in && !IsValidCharacter(*in))
    in++;
  return in;
}
