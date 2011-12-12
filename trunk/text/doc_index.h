// $Id: doc_index.h 3581 2011-06-10 14:36:56Z haowu $

#ifndef _ETC_DOC_INDEX_H_
#define _ETC_DOC_INDEX_H_

#include "../base.h"
#include "../util/util.h"

struct DocIndex
{
  DocIndex();
  void Build(const vector<string>& z_str);
  void Build(const vector<string>& z_str, const char* stop_word_file);
  //
  set<string>                 sw_; // set of stop words
  vector<string>          z_wstr_;
  map<string, int>      m_wstr_w_;
  vector<vector<int> >      zz_d_; // inverted index
  vector<set<int> >         zs_w_; // forward index
  vector<double>           z_idf_; // idf's
};

#endif
