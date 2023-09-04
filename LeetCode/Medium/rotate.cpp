#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/*
   https://leetcode.com/explore/learn/card/array-and-string/204/conclusion/1182/
   Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

   Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]


Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]


Constraints:

1 <= nums.length <= 105
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 105


Follow up:

Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?

Solution: O(1) extra space, O(n) time in-place algorithm

Algorithm summary:
1. shift each element k places to the right(if index overflows, modulo it) using a temp variable to store the element in the kth index from current index.
2. Special cases arise when array size and k happen to have a gcd that is not 1: In these cases, the algorithm tends to loop over the same cycle without 
	covering all elements. Solution to this is:
			When we land back at the starting position of a loop, we shift one position right. Rinse and repeat.

Implementation:
1. If size of the array is 1, just exit.
2. If k is equal to or over the size of the array, modulo it with the size.
3. If k is now zero, exit else continue.
4. Initalize two temporary variable t1 and t2 to 1st element and kth element, respectively.
5. Initialize a variable index to keep track of the index of the element which we'll change in due course.
6. For special case mentioned above
	a. Initialize a variable called tempIndex to zero.
	b. Initialize a variable resetLoopCount to size/gcd of size and k.
7. If resetLoopCount happens to be the size of arry, set it to zero.
	
8. Now, run a loop for 'size of the array' times. At each iteration, do the following:
	a. Set the index as current position + k (modulo with size if the index overflows)
	b. Set nums[index] as t1
	c. Swap t1 and t2
	d. If this is THE special case and the loop count is a multiple of rLC, then we're at the beginning of a loop. So:
		i. Increment tempIndex
		ii. Set t1 as nums[tempIndex]
		iii. Set t2 as the element k indices to the right of t1 (modulo with size if index overflows)
			Above three steps sets a new set of t1 and t2.
		iv. Increment index (this derails us from the loop)
		v. Goto the next iteration.
	e. Set t2 as the element k indices to the right of t1 (modulo with size if index overflows)
9. Now we have the rotated array
 */

void rotate(std::vector<int>& nums, int k) {
    if(nums.size() == 1)
	return;

    auto size{ static_cast<int>(nums.size()) };

    //reduce k
    if(k >= size)
    {
	k = k % size;
    }

    if(k == 0)
	return;

    int t1{ nums[0] };
    int t2{ nums[k] };
    int index{};

    int tempIndex{};	//for use in special case only
    int resetLoopCount{ size/std::gcd(size, k)}; //for use in special case only

    if(resetLoopCount == size)
	resetLoopCount = 0;

    for(auto i{ 0 }; i < size; ++i)
    {
	if(index + k >= size)
	{
	    index = (index + k) % size;
	}
	else
	{
	    index = index + k;
	}

	nums[index] = t1;
	std::swap(t1, t2);

	//Special case
	if(resetLoopCount && ((i + 1) % resetLoopCount == 0))
	{
	    ++tempIndex;
	    t1 = nums[tempIndex];
	    if(tempIndex + k >= size)
	    {
		t2 = nums[(tempIndex + k) % size];
	    }
	    else
	    {
		t2 = nums[tempIndex + k];
	    }
	    ++index;
	    continue;
	}

	if(index + k >= size)
	{
	    t2 = nums[(index + k) % size];
	}
	else
	{
	    t2 = nums[index + k];
	}
    }
}

int main()
{
    std::vector<int> v;

    std::cout << "Enter size: ";
    int size;
    std::cin >> size;

    for(auto i{ 0 }; i < size; ++i)
    {
	v.push_back(i + 1);
    }
    for(const auto ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';

    std::cout<<"Enter shift count: ";
    int k;
    std::cin >> k;
    rotate(v, k);
    for(const auto ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';
}
