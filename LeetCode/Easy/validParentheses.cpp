#include <iostream>
#include <stack>
#include <string>

class Solution {
    public:
	bool isValid(std::string s) {
	    std::stack<char> stk;

	    //traverse through the string.
	    for(auto ch: s) {

		//opening parenth. are pushed onto stack.
		if(ch == '(' || ch == '{' || ch == '[') {
		    stk.push(ch);
		}
		else {
		    if(stk.size()) {
			//close parenth are matched with corresponding open ones on top of stack.
			if(ch == ')') {
			    if(stk.top() == '(') {
				stk.pop();
			    } else {
				return false;
			    }
			}

			if(ch == '}') {
			    if(stk.top() == '{') {
				stk.pop();
			    } else {
				return false;
			    }
			}

			if(ch == ']') {
			    if(stk.top() == '[') {
				stk.pop();
			    } else {
				return false;
			    }
			}
		    } else
			return false;
		}
	    }

	    //by the end of traversal, stack must be empty.
	    if(stk.size())
		return false;
	    else
		return true;
	}
};

int main()
{
    Solution s;
    std::string str;
    std::cout << "Enter string: ";
    std::cin >> str;
    std::cout << ((s.isValid(str))? "True": "False") << '\n';
}

