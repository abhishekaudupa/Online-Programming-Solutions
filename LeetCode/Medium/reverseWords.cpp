#include <iostream>
#include <string>

/*
   Reverse Words in a String
   https://leetcode.com/explore/learn/card/array-and-string/204/conclusion/1164/

   Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.



Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.


Constraints:

1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.


Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?

Solution:
	1. Remove all leading/lagging/extra spaces.
	2. Reverse the string array entirely (like a vanilla array reverse).
	3. Reverse individual words.
   */


std::string reverseWords(std::string s) {
    auto len{ s.size() };

    //First clear all extra spaces
    int spaceCtr{ };
    for(auto i{ 0 }; i < len; ++i)
    {
	//std::cout << s[i] << '\n';
	if(i == 0 && s[i] == ' ')
	{
	    ++spaceCtr;
	}
	else if(s[i] == ' ' && s[i - 1] == ' ')
	{
	    ++spaceCtr;
	}
	else
	{
	    s[i - spaceCtr] = s[i];
	}
    }
    s.erase(len - spaceCtr, spaceCtr);
    if(s[s.size() - 1] == ' ')
    {
	s.erase(s.size() - 1, 1);
    }


    //reverse the array
    len = s.size();
    for(auto i{ 0 }; i < len - i; ++i)
    {
	std::swap(s[i], s[len - i - 1]);
    }

    //reverse individual words
    for(auto i{ 0 }; i < len; )
    {
	if(s[i] == ' ')
	{
	    ++i;
	    continue;
	}

	auto j{ i + 1 };

	while(s[j] != ' ' && j < len)
	    ++j;
	--j;

	auto wLen{ j - i + 1 };
	auto k{ i };

	while(j > k)
	{
	    std::swap(s[k], s[j]);
	    ++k, --j;
	}

	i += wLen;
    }

    return s;
}

int main()
{
    std::string s{ "      Abhishek's a      good    boy!" };
    std::cout << s << '\n';
    std::string sr{ reverseWords(s) };
    std::cout << sr << '\n';
}

