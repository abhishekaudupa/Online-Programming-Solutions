#include <iostream>
#include <vector>
#include <stack>

/*
   Daily Temperatures

   Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.



Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]


Constraints:

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100

Solution:
	We traverse through the array and while traversing, we check if the
	next day's temperature is greater than current day's. If it is, then
	we have 1 day to get a warmer temperature. Otherwise, we don't know
	when we'll get a warmer temperature next. So we push the current day
	onto a stack.

	Next time we see a temperature climb, we check the next day's temperature
	with the last day when we noticed a drop in temperature (stack's top
	entry). If that day's temperature is lower than the next day's temperature
	then we can calculate the difference of days between next day and that
	day and put that number under that day's entry and keep doing the same
	as long as next day's temperature is greater than the stack's topmost 
	entry.

	We do this till we've traversed the penultimate entry in the list. The
	last day's answer would be zero by default. If there are anymore entries
	left in the stack, it means those days don't get to meet warmer days
	in the future (as far as that list goes).

Algorithm: Code is self-explanatory and simple.
 
 */

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        
	std::vector<int> answer(temperatures.size());
	std::stack<int> days;

	//traverse the vector till penultimate day.
	for(auto i = 0u; i < temperatures.size() - 1; ++i) {

	    //check if next day's temp. is greater.
	    if(temperatures[i + 1] > temperatures[i]) {
		//one day to feel warmer.
		answer[i] = 1;

		//check if the next day's temp. is greater than stack.top day's.
		while(!days.empty()) {
		    if(temperatures[i + 1] > temperatures[days.top()]) {
			answer[days.top()] = i + 1 - days.top();
			days.pop();
		    } else {
			break;
		    }
		}
	    } else {
		//push that day into a stack.
		days.push(i);
	    }
	}

	//days that didn't see a warmer day in the future.
	while(!days.empty()){
	    answer[days.top()] = 0;
	    days.pop();
	}

	//last day.
	answer[temperatures.size() - 1] = 0;
	return answer;
    }
};

int main()
{
    std::vector<int> v{ 10, 1, 2, 3, 4, 3, 2, 1, 3};
    Solution s;
    std::vector<int> ans = s.dailyTemperatures(v);

    for(auto ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';

    for(auto ele: ans)
	std::cout << ele << ' ';
    std::cout << '\n';
}

