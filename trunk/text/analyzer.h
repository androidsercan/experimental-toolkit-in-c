// $Id: analyzer.h 3698 2011-07-07 14:04:52Z haowu $

#ifndef _ETC_TEXT_ANALYZER_H_
#define _ETC_TEXT_ANALYZER_H_

#include "../base.h"
#include "../util/util.h"

class Analyzer
{
public:
  Analyzer();
  Analyzer(const string& sw_file);
  void AddStopWord(const string& word);
  void Tokenize(const string& str, vector<string>* z_word) const;
protected:
  set<string> s_sw_;
  //
  bool IsValidCharacter(char c) const;
  const char* Tokenize(const char* in, char* out) const;
};

#endif
