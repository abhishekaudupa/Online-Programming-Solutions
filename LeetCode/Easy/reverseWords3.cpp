#include <iostream>
#include <string>

/*
   Reverse Words in a String III
https://leetcode.com/explore/learn/card/array-and-string/204/conclusion/1165/

Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:

Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Example 2:

Input: s = "God Ding"
Output: "doG gniD"


Constraints:

1 <= s.length <= 5 * 104
s contains printable ASCII characters.
s does not contain any leading or trailing spaces.
There is at least one word in s.
All the words in s are separated by a single space.

Solution:
	1. Note the first letter of a word.
	2. Then find the last letter of the same word.
	3. Do a vanilla array reverse on the word now that you know start and end indices of the word.
	4. Advance to next word.	
 */


std::string reverseWords(std::string s) {
    auto len{ s.size() };

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
    std::string s{ "Let's take LeetCode contest" };
    std::cout << s << '\n';
    std::string sr{ reverseWords(s) };
    std::cout << sr << '\n';
}

