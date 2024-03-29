// $Id: vbe.h 3581 2011-06-10 14:36:56Z haowu $

#ifndef _ETC_VBE_H_
#define _ETC_VBE_H_

#include <assert.h>
#include <vector>

using namespace std;

class VBE // Variable Byte Encoding
{
public:
	VBE();
	~VBE();
	char* Encode(const vector<int>& nums, int& len);
	void Decode(char* buf, int len, vector<int>& nums);
private:
  void Encode(int num, char buf[16]);
};

#endif
