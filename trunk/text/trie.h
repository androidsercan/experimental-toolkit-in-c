// $Id: trie.h 4299 2011-09-26 08:16:24Z haowu $

#ifndef _ETC_TEXT_TRIE_H_
#define _ETC_TEXT_TRIE_H_

#include <string>
#include <vector>

using namespace std;

//
//
//

struct BaseTrieNode
{
  BaseTrieNode()
    : c_(0), p_parent_(NULL), p_prev_sibling_(NULL), p_next_sibling_(NULL), p_first_child_(
    NULL), p_last_child_(NULL)
  {
  }
  //
  char c_;
  BaseTrieNode* p_parent_;
  BaseTrieNode* p_prev_sibling_;
  BaseTrieNode* p_next_sibling_;
  BaseTrieNode* p_first_child_;
  BaseTrieNode* p_last_child_;
};

//
//
//

void BaseTrie_Init(BaseTrieNode** pp_bt_root);
void BaseTrie_Add(const char* str, BaseTrieNode* p_bt_root);
void BaseTrie_Find(const char* str, const BaseTrieNode& bt_root,
    BaseTrieNode** pp_result);
void BaseTrie_Destroy(BaseTrieNode* p_bt_root);

//
//
//

struct RadixTrieNode
{
  struct Compare
  {
    bool operator ()(RadixTrieNode* p1, RadixTrieNode* p2)
    {
      return (p1->str_.c_str())[0] < (p2->str_.c_str())[0];
    }
  };
  //
  RadixTrieNode()
      : id_(-1), str_(""), p_parent_(NULL)
  {
  }
  //
  int id_;
  string str_;
  vector<char> z_c_;
  RadixTrieNode* p_parent_;
  vector<RadixTrieNode*> zp_child_;
};

//
//
//

void RadixTrie_Init(const BaseTrieNode& bt_root, RadixTrieNode** pp_rt_root);
void RadixTrie_AssignIDs(RadixTrieNode* p_rt_root, int* p_begin);
void RadixTrie_Find(const char* str, const RadixTrieNode& rt_root,
    RadixTrieNode** pp_result);
void RadixTrie_Destroy(RadixTrieNode* p_rt_root);
int  RadixTrie_GetSizeInByte(const RadixTrieNode& rt_root);

//
//
//

/*
 * It is recommended to use this Trie class instead of above C-style functions
 */
class Trie
{
public:
  Trie();
  Trie(const vector<string>& z_str, char eos);
  ~Trie();
  void Build(const vector<string>& z_str, char eos);
  void Find(const string& str, RadixTrieNode** pp_result) const;
  pair<int, int> GetInterval(int nid) const;
  int GetNumString() const;
  int GetNumNode() const;
  int GetSizeInByte() const;
protected:
  void CalculateIntervals(RadixTrieNode* p_node);
  //
  RadixTrieNode* p_root_;
  vector<pair<int, int> > z_interval_; // intervals, indexed by node ids
  int n_leaf_node_;
  int n_node_;
};

//
//
//

#endif
