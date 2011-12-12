// $Id: dictionary.h 3698 2011-07-07 14:04:52Z haowu $

/*
 * dictionary.h
 *
 *  Created on: Jul 6, 2011
 *      Author: Hao Wu
 */

#ifndef _ETC_TEXT_DICTIONARY_H_
#define _ETC_TEXT_DICTIONARY_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

class Dictionary
{
public:
  Dictionary();
  void Clear();
  int Add(const string& str);
  int GetStringId(const string& str) const;
  const string& GetString(int s) const;
  int GetSize() const;
protected:
  map<string, int> m_str_s_;
  vector<string> z_str_;
};

#endif /* _ETC_TEXT_DICTIONARY_H_ */
