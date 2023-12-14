#include <iostream>
#include <vector>

/*

   Target Sum

   You are given an integer array nums and an integer target.

   You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

   For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
   Return the number of different expressions that you can build, which evaluates to target.



   Example 1:
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:
Input: nums = [1], target = 1
Output: 1


Constraints:

1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000

Solution: This is basically a combinatorics problem. See comments in code for the solution.
		This is a recursive solution and conceptually easy to understand.

 */

class Solution {
    public:

	int findWays(std::vector<int>& nums, int target, int r_depth, int curr_sum) {

	    /* Recursive case:
	       We'll recursively flip sign of element at index r_depth 
	       and add it to element at index 'r_depth + 1'. We do this
	       till all elements of the array are added up.
	       This has the effect of trying out all possible sums.
	       Visualize this like a tree.
	     */
	    if(r_depth < nums.size()) {
		return findWays(nums, target, r_depth + 1, curr_sum + nums[r_depth]) + findWays(nums, target, r_depth + 1, curr_sum - nums[r_depth]);
	    }

	    /* Base case:
	       After adding all elements with all possible signs, see if
	       it adds up to target. If so we return 1 - a 'yes, we reached target'.
	       This bubble up along each branch of the tree where it gets added up with
	       the return value of the other branch, at the root node and bubbles up
	       even higher till the main root node.
	     */
	    if(curr_sum == target)
		return 1;
	    else
		return 0;
	}

	int findTargetSumWays(std::vector<int>& nums, int target) {
	    return findWays(nums, target, 0, 0);
	}
};

int main() {
    std::vector<int> nums = {1};
    Solution s;
    int n;
    std::cin >> n;
    std::cout << s.findTargetSumWays(nums, n) << '\n';
}

