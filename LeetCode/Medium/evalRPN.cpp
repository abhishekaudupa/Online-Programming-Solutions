#include <iostream>
#include <vector>
#include <string>
#include <stack>

/*
   Evaluate Reverse Polish Notation

   You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

Evaluate the expression. Return an integer that represents the value of the expression.

Note that:

The valid operators are '+', '-', '*', and '/'.
Each operand may be an integer or another expression.
The division between two integers always truncates toward zero.
There will not be any division by zero.
The input represents a valid arithmetic expression in a reverse polish notation.
The answer and all the intermediate calculations can be represented in a 32-bit integer.


Example 1:

Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22


Constraints:

1 <= tokens.length <= 104
tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].

Solution: Standard. You can google. It's all over the place.

   */

class Solution {
public:

    inline bool isOperator(const std::string& character) {
	return ((character[0] == '+' && character[1] == 0)
	|| (character[0] == '-' && character[1] == 0)
	|| character[0] == '*'
	|| character[0] == '/');
    }

    inline int doOper(const int operand1, const int operand2, const std::string& optr) {

	if(optr[0] == '+')
	    return operand1 + operand2;
	
	if(optr[0] == '-')
	    return operand1 - operand2;

	if(optr[0] == '*')
	    return operand1 * operand2;

	if(optr[0] == '/')
	    return operand1 / operand2;

	return 0;
    }

    int evalRPN(std::vector<std::string>& tokens) {
	
	//stack to store intermediate and final results.
	std::stack<int> res;

	//traverse token list.
	for(auto ele: tokens) {
	    if(isOperator(ele)) {
		int operand2 = res.top();
		res.pop();
		int operand1 = res.top();
		res.pop();
		res.push(doOper(operand1, operand2, ele));
	    } else {
		res.push(stoi(ele));
	    }
	}

	return res.top();
    }
};

int main()
{
    Solution s;
    std::vector<std::string> rpn{ "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"  };
    int res = s.evalRPN(rpn);

    for(auto ele: rpn)
	std::cout << ele << ' ';
    std::cout << " = " << res << '\n';
}

