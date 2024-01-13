#include <iostream>
#include <unordered_map>

/*
   Climbing Stairs

   You are climbing a staircase. It takes n steps to reach the top.

   Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?



   Example 1:

   Input- n = 2
   Output- 2
   Explanation- There are two ways to climb to the top.
   1. 1 step + 1 step
   2. 2 steps
   Example 2:

   Input- n = 3
   Output- 3
   Explanation- There are three ways to climb to the top.
   1. 1 step + 1 step + 1 step
   2. 1 step + 2 steps
   3. 2 steps + 1 step


   Constraints-

   1 <= n <= 45

   Solution - O(n), memoized. Code self explanatory.
 */

class Solution {
    std::unordered_map<int, int> store;

    public:
    int climbStairs(int n) {
	if(store.find(n) != store.end())
	    return store.at(n);

	if(n == 1) {
	    store.insert(std::make_pair(1, 1));
	    return 1;
	}

	if(n == 2) {
	    store.insert(std::make_pair(2, 2));
	    return 2;
	}

	int count = climbStairs(n - 1) + climbStairs(n - 2);
	store.insert(std::make_pair(n, count));
	return count;
    }
};

int main() {
    std::cout << "Enter n: ";
    int n;
    std::cin >> n;
    Solution s;
    std::cout << s.climbStairs(n) << '\n';
}

