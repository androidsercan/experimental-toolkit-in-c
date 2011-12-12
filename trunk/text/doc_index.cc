// $Id: doc_index.cc 3573 2011-06-10 07:29:27Z haowu $

#include "doc_index.h"

#include <cmath>

using namespace std;

DocIndex::DocIndex()
{
}

void DocIndex::Build(const vector<string>& z_str)
{
  Build(z_str, NULL);
}

void DocIndex::Build(const vector<string>& z_str, const char* stop_word_file)
{
  sw_.clear();
  z_wstr_.clear();
  m_wstr_w_.clear();
  zz_d_.clear();
  //
  // build inverted index
  //
  if (stop_word_file != NULL) {
    char buff[MAX_KEYWORD_LENGTH];
    buff[0] = 0;
    sw_.insert(buff);
    FILE* f = fopen(stop_word_file, "r");
    while (EOF != fscanf(f, "%s", buff))
      sw_.insert(buff);
    fclose(f);
  }
  //
  // build inverted index and forward index
  //
  for (int i = 0; i < (int)z_str.size(); i++) {
    zs_w_.push_back(set<int>());
    const char* p = (z_str[i]).c_str();
    while (*p) {
      char buff[0x100];
      p = Util::Tokenize(p, buff);
      if (sw_.find(buff) != sw_.end()) {
        continue;
      }
      int wid;
      string wstr = string(buff);
      map<string, int>::iterator j = m_wstr_w_.find(wstr);
      if (j == m_wstr_w_.end()) {
        wid = z_wstr_.size();
        z_wstr_.push_back(wstr);
        m_wstr_w_.insert(pair<string, int>(wstr, wid));
        zz_d_.push_back(vector<int>());
      } else {
        wid = j->second;
      }
      zz_d_[wid].push_back(i);
      zs_w_[i].insert(wid);
    }
  }
  //
  // calculate IDFs
  //
  for (int i = 0; i < (int)zz_d_.size(); i++) {
    int D  = z_str.size();
    int Di = zz_d_[i].size();
    double idf = log((double)D / (double)Di);
    z_idf_.push_back(idf);
  }
}
