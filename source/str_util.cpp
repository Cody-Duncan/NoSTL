#include "str_util.h"
#include "z_assert.h"

//search for a substring, starting at the end
//returns the index of the start of the substring, or -1 if not found
int strr(const char* str, int pos, const char* pattern, int b1_len, int b2_len) 
{
	z_assert_message(str != nullptr, "string to search is null");
	z_assert_message(pattern != nullptr, "pattern is null");
	z_assert_message(pos >= 0, "start index below array index range");
	z_assert_message(pos <= b1_len, "start index above array index range");
	z_assert_message(b1_len >= b2_len, "string to search is smaller than pattern to find");

	if (b1_len == pos && 
		b2_len == 0) 
		return pos;

	if (b2_len == 0) 
		return pos;

	if (str == pattern && 
		pos == 0 && 
		b2_len <= b1_len) 
		return 0;

	int i = pos; //start of str
	int j = 0;   //start of pattern

	// if i is after where pattern could start, move back to where pattern would start.
	int len_delta = b1_len - b2_len;
	if(len_delta + 1 <= i)
	{
		i = len_delta;
	}

	for (;;) 
	{
		if (pattern[j] == str[i + j]) 
		{
			++j;
			if(j >= b2_len)
			{
				return i;
			}
				
		} 
		else 
		{
			--i;
			if(i < 0)
			{
				break;
			}
			j=0;
		}
	}

	return -1;
}