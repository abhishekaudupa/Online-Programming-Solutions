#include <iostream>
#include <vector>

/*Solution for https://leetcode.com/explore/learn/card/array-and-string/205/array-two-pointer-technique/1299/

Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0


Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104
*/

int minSubArrayLen(int target, std::vector<int>& nums) {
    if(nums.size() == 1)
    {
	return ((nums[0] >= target)? 1: 0);
    }
    int len{ 100001 };
    auto p1{ 0 };
    auto p2{ 0 };
    int sum{ nums[p1] };

    while(1)
    {
	//std::cout << sum << ',' << p1 << ',' << p2 << ',' << len << '\n';
	if(sum >= target)
	{
	    if(p2 - p1 + 1 < len)
	    {
		len = p2 - p1 + 1;
		if(len == 1)
		    return len;
	    }

	    if(p1 < p2)
	    {
		sum -= nums[p1++];
	    }
	    else
	    {
		if(p1 == nums.size() - 1)
		{
		    break;
		}
	    }
	}
	else
	{
	    if(p2 < nums.size() - 1)
	    {
		sum += nums[++p2];
	    }
	    else
	    {
		if(p2 == nums.size() - 1)
		{
		    break;
		}
	    }
	}
    }

    return ((len == 100001)? 0: len);
}

int main()
{
    std::vector<int> v{2,3,1,2,3,4};
    std::cout << "Enter n: ";
    int n{};
    std::cin >> n;
    std::cout << minSubArrayLen(n, v) << '\n';
}
