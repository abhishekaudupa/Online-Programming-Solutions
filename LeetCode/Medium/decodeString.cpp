#include <iostream>
#include <string>
#include <stack>

/*
   Decode String

   Given an encoded string, return its decoded string.

   The encoding rule is: k[encoded_string], where the encoded_string 
   inside the square brackets is being repeated exactly k times. Note 
   that k is guaranteed to be a positive integer.

   You may assume that the input string is always valid; there are no 
   extra white spaces, square brackets are well-formed, etc. 
   Furthermore, you may assume that the original data does not contain 
   any digits and that digits are only for those repeat numbers, k. 
   For example, there will not be input like 3a or 2[4].

   The test cases are generated so that the length of the output will 
   never exceed 105.

   Example 1

   Input s = "3[a]2[bc]"
   Output "aaabcbc"

   Example 2

   Input s = "3[a2[c]]"
   Output "accaccacc"

   Example 3

   Input s = "2[abc]3[cd]ef"
   Output "abcabccdcdcdef"


   Constraints

   1 <= s.length <= 30
   s consists of lowercase English letters, digits, and square brackets '[]'.
   s is guaranteed to be a valid input.
   All the integers in s are in the range [1, 300].

   Solution - O(n).
   1. Numbers are pushed to count stack.
   2. Open bracket is pushed to string stack.
   3. Alphabets are pushed to string stack on top of open brackets.
   4. If we encounter a closed bracket
   	a. Topmost string in string stack is appended to itself for
   	number of times as dictated by the topmost number in count
   	stack.
   	b. Topmost element of count stack is popped.
   	c. Topmost element of string stack is noted and the stack
   	is popped twice.
   		- Topmost string is noted.
   		- Open bracket below it is thrown away.
   	d. If string stack still has atleast one element in it and
	the top element is not an open bracket, then
   		- The noted string is appended to topmost string.
   		- else noted string is pushed.
 */

class Solution {
    public:
	std::string decodeString(const std::string& s) {

	    //get a stacks to track digits and non-digits.
	    std::stack<std::string> s_stack;
	    std::stack<unsigned int> n_stack;

	    //start input string traversal
	    for(size_t i = 0; i < s.size(); ) {

		//if you encounter a digit.
		if(s[i] >= '0' && s[i] <= '9') {
		    //capture the entire digit.
		    unsigned int count = 0;
		    size_t j = i;
		    for(; s[j] >= '0' && s[j] <= '9'; ++j)
			count = count * 10 + (s[j] - '0');

		    //increment i.
		    i = j;

		    //push the count into count stack.
		    n_stack.push(count);

		    continue;
		}

		//if closing bracket is encountered.
		if(s[i] == ']') {

		    //expand the string, if possible.
		    auto s_temp = s_stack.top();
		    for(size_t k = 1; k < n_stack.top(); ++k)
			s_stack.top() += s_temp;

		    //discard topmost count.
		    n_stack.pop();

		    //discard opening braket.
		    s_temp = s_stack.top();
		    s_stack.pop();
		    s_stack.pop();

		    //append it to previous string, if possible.
		    if(s_stack.size() > 0) {
			if(s_stack.top() != "[") {
			    s_stack.top() += s_temp;
			} else {
			    s_stack.push(s_temp);
			}
		    } else {
			s_stack.push(s_temp);
		    }

		    //continue.
		    ++i;
		    continue;
		}

		//if opening bracket is encountered.
		if(s[i] == '[') {

		    //push it to string stack.
		    s_stack.push(std::string(1, '['));

		    //continue.
		    ++i;
		    continue;
		}

		//if alphabets are encountered.

		if(s_stack.empty()) {
		    s_stack.push(std::string(1, s[i++]));
		} else {
		    if(s_stack.top() == "[")
			s_stack.push(std::string(1, s[i++]));
		    else
			s_stack.top() += s[i++];
		}
	    }

	    return s_stack.top();
	}
};

int main() {
    Solution s;
    //auto str = "3[z]2[2[y]pq4[2[jk]e1[f]]]ef";
    //auto str = "3[ab2[c]2[d2[x]]]";
    //auto str = "2[abc]3[cd]ef";
    //auto str = "abc3[cd]xyz";
    auto str = "100[leetcode]";
    std::cout << "I/p: " << str << '\n';
    auto dstr = s.decodeString(str);
    std::cout << "Final: " << dstr << '\n';
}

