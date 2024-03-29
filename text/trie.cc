// $Id: trie.cc 4175 2011-08-24 12:52:39Z haowu $

#include "trie.h"
#include "../util/search.h"
//
#include <vector>
#include <algorithm>

using namespace std;

//
//
//

//
// BaseTrie
//

//
//
//

void BaseTrie_Init(BaseTrieNode** pp_bt_root)
{
  *pp_bt_root = new BaseTrieNode();
}

//
//
//

void BaseTrie_Add(const char* str, BaseTrieNode* p_bt_root)
{
  if (*str == '\0') {
    return;
  }
  BaseTrieNode* p_next = NULL;
  BaseTrieNode* p_child = p_bt_root->p_first_child_;
  while (p_child != NULL) {
    if (p_child->c_ == *str) {
      p_next = p_child;
      break;
    }
    p_child = p_child->p_next_sibling_;
  }
  if (p_next == NULL) {
    p_next = new BaseTrieNode();
    p_next->c_ = *str;
    p_next->p_parent_ = p_bt_root;
    if (p_bt_root->p_first_child_ == NULL) {
      p_bt_root->p_first_child_ = p_next;
    } else {
      p_bt_root->p_last_child_->p_next_sibling_ = p_next;
      p_next->p_prev_sibling_ = p_bt_root->p_last_child_;
    }
    p_bt_root->p_last_child_ = p_next;
  }
  BaseTrie_Add(str + 1, p_next);
}

//
//
//

void BaseTrie_Find(const char* str, const BaseTrieNode& bt_root,
    BaseTrieNode** pp_result)
{
  if (*str == '\0') {
    *pp_result = (BaseTrieNode*)&bt_root;
    return;
  }
  BaseTrieNode* p_next = NULL;
  BaseTrieNode* p_child = bt_root.p_first_child_;
  while (p_child != NULL) {
    if (p_child->c_ == *str) {
      p_next = p_child;
      break;
    }
    p_child = p_child->p_next_sibling_;
  }
  if (p_next != NULL) {
    BaseTrie_Find(str + 1, *p_next, pp_result);
  } else {
    *pp_result = NULL;
  }
}

//
//
//

void BaseTrie_Destroy(BaseTrieNode* p_bt_root)
{
  BaseTrieNode* p_child = p_bt_root->p_first_child_;
  while (p_child != NULL) {
    BaseTrieNode* p_next_sibling = p_child->p_next_sibling_;
    BaseTrie_Destroy(p_child);
    p_child = p_next_sibling;
  }
  delete p_bt_root;
}

//
//
//

//
// RadixTrie
//

//
//
//

void RadixTrie_Init(const BaseTrieNode& bt_root, RadixTrieNode** pp_rt_root)
{
  *pp_rt_root = new RadixTrieNode();
  //
  RadixTrieNode* p_rt_root = *pp_rt_root;
  BaseTrieNode* p = (BaseTrieNode*)(&bt_root);
  if (p->c_ != '\0') {
    p_rt_root->str_ += p->c_;
  }
  while (p->c_ != '\0' && p->p_first_child_ != NULL
      && p->p_first_child_ == p->p_last_child_) {
    p = p->p_first_child_;
    p_rt_root->str_ += p->c_;
  }
  //
  BaseTrieNode* q = p->p_first_child_;
  while (q != NULL) {
    RadixTrieNode* p_child;
    RadixTrie_Init(*q, &p_child);
    p_child->p_parent_ = p_rt_root;
    p_rt_root->zp_child_.push_back(p_child);
    q = q->p_next_sibling_;
  }
  //
  sort(p_rt_root->zp_child_.begin(), p_rt_root->zp_child_.end(),
      RadixTrieNode::Compare());
  //
  vector<RadixTrieNode*>::iterator iter = p_rt_root->zp_child_.begin();
  while (iter != p_rt_root->zp_child_.end()) {
    p_rt_root->z_c_.push_back(((*iter)->str_.c_str())[0]);
    ++iter;
  }
}

//
//
//

void RadixTrie_AssignIDs(RadixTrieNode* p_rt_root, int* p_begin)
{
  p_rt_root->id_ = *p_begin;
  (*p_begin)++;
  vector<RadixTrieNode*>::iterator iter = p_rt_root->zp_child_.begin();
  while (iter != p_rt_root->zp_child_.end()) {
    RadixTrie_AssignIDs(*iter, p_begin);
    ++iter;
  }
}

//
//
//

void RadixTrie_Find(const char* str, const RadixTrieNode& rt_root,
    RadixTrieNode** pp_result)
{
  if (*str == '\0') {
    *pp_result = (RadixTrieNode*)&rt_root;
    return;
  }
  //
  int bias = 0;
  RadixTrieNode* p_next = NULL;
  //
  const vector<char>& z_c = rt_root.z_c_;
  vector<char>::const_iterator iter;
  Flag f = BinarySearch(str[0], z_c.begin(), z_c.end(), &iter);
  if (f == SUCCESS) {
    int i = iter - z_c.begin();
    RadixTrieNode* p_child = rt_root.zp_child_[i];
    bool matching = true;
    const char* str_child = p_child->str_.c_str();
    while (true) {
      if (str[bias] == '\0' || str_child[bias] == '\0') {
        break;
      }
      if (str[bias] != str_child[bias]) {
        matching = false;
        break;
      }
      bias++;
    }
    if (matching) {
      p_next = p_child;
    }
  }
  if (p_next != NULL) {
    RadixTrie_Find(str + bias, *p_next, pp_result);
  } else {
    *pp_result = NULL;
  }
}

//
//
//

void RadixTrie_Destroy(RadixTrieNode* p_rt_root)
{
  vector<RadixTrieNode*>::const_iterator iter = p_rt_root->zp_child_.begin();
  while (iter != p_rt_root->zp_child_.end()) {
    RadixTrie_Destroy(*iter);
    ++iter;
  }
  delete p_rt_root;
}

//
//
//

int RadixTrie_GetSizeInByte(const RadixTrieNode& rt_root)
{
  int sz = 0;
  sz += sizeof(int); // id_
  sz += rt_root.str_.length() * sizeof(char); // str_
  sz += sizeof(RadixTrieNode*); // p_parent_
  sz += rt_root.zp_child_.size() * sizeof(RadixTrieNode*); // zp_child_
  for (int i = 0; i < (int)rt_root.zp_child_.size(); i++) {
    sz += RadixTrie_GetSizeInByte(*(rt_root.zp_child_[i]));
  }
  return sz;
}

//
//
//

//
// Trie
//

//
//
//

Trie::Trie()
{
}

//
//
//

Trie::Trie(const vector<string>& z_str, char eos)
{
  Build(z_str, eos);
}

//
//
//

Trie::~Trie()
{
  RadixTrie_Destroy(p_root_);
}

//
//
//

void Trie::Build(const vector<string>& z_str, char eos)
{
  //
  // build radix trie
  //
  BaseTrieNode* p_bt_root;
  BaseTrie_Init(&p_bt_root);
  for (int i = 0; i < (int)z_str.size(); i++) {
    string str = z_str[i] + eos;
    BaseTrie_Add(str.c_str(), p_bt_root);
  }
  RadixTrie_Init(*p_bt_root, &p_root_);
  BaseTrie_Destroy(p_bt_root);
  //
  // assign ids to nodes
  //
  n_node_ = 0;
  RadixTrie_AssignIDs(p_root_, &n_node_);
  //
  // for each node, calculate the interval of string ids
  //
  z_interval_.resize(n_node_);
  n_leaf_node_ = 0;
  CalculateIntervals(p_root_);
}

//
//
//

void Trie::Find(const string& str, RadixTrieNode** pp_result) const
{
  RadixTrie_Find(str.c_str(), *p_root_, pp_result);
}

//
//
//

pair<int, int> Trie::GetInterval(int nid) const
{
  return z_interval_[nid];
}

//
//
//

int Trie::GetNumString() const
{
  return n_leaf_node_;
}

//
//
//

int Trie::GetNumNode() const
{
  return n_node_;
}

//
//
//

int Trie::GetSizeInByte() const
{
  int sz = 0;
  sz += sizeof(RadixTrieNode*); // p_root_
  sz += z_interval_.size() * sizeof(int) * 2; // z_interval_
  sz += sizeof(int); // n_leaf_node_
  sz += sizeof(int); // n_node_
  sz += RadixTrie_GetSizeInByte(*p_root_);
  return sz;
}

//
//
//

void Trie::CalculateIntervals(RadixTrieNode* p_node)
{
  int lb = 0;
  int ub = 0;
  if (p_node->zp_child_.size() == 0) {
    lb = n_leaf_node_;
    ub = n_leaf_node_;
    n_leaf_node_++;
  } else {
    vector<RadixTrieNode*>::iterator iter = p_node->zp_child_.begin();
    while (iter != p_node->zp_child_.end()) {
      CalculateIntervals(*iter);
      ++iter;
    }
    lb = z_interval_[p_node->zp_child_.front()->id_].first;
    ub = z_interval_[p_node->zp_child_.back()->id_].second;
  }
  z_interval_[p_node->id_] = make_pair(lb, ub);
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
