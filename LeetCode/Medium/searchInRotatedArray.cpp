#include <iostream>
#include <vector>

/*
   Search in rotated sorted array.

   There is an integer array nums sorted in ascending order (with distinct values).

   Prior to being passed to your function, nums is possibly rotated at an unknown 
   pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], 
   nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For 
   example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become 
   [4,5,6,7,0,1,2].

   Given the array nums after the possible rotation and an integer target, return 
   the index of target if it is in nums, or -1 if it is not in nums.

   You must write an algorithm with O(log n) runtime complexity.



   Example 1:

   Input- nums = [4,5,6,7,0,1,2], target = 0
   Output- 4
   Example 2:

   Input- nums = [4,5,6,7,0,1,2], target = 3
   Output- -1
   Example 3:

   Input- nums = [1], target = 0
   Output- -1


   Constraints-

   1 <= nums.length <= 5000
   -104 <= nums[i] <= 104
   All values of nums are unique.
   nums is an ascending array that is possibly rotated.
   -104 <= target <= 104

   Solution - O(log n).
   First we get the pivot index (log n TC).
   	- Find middle element.
	- If the array from first to middle element is in
	ascending order, the second part is rotated and
	vice-versa.

   Next we binary search on the relevant array range. 
   
   Code self-explanatory.
 */

class Solution {

    int binarySearch(std::vector<int>& nums, int start, int end, int target) {

	//standard binary search.
	while(start <= end) {
	    auto mid = (start + end) / 2;

	    if(nums[mid] == target)
		return mid;

	    if(target < nums[mid])
		end = mid - 1;
	    else
		start = mid + 1;
	}

	return -1;
    }

    inline int findPivot(std::vector<int>& nums) {

	auto start = 0;
	auto end = nums.size() - 1;

	//non-rotated array, pivot index is 0.
	if(nums[start] < nums[end])
	    return start;

	//rotated array.

	//repeatedly search rotated array.
	while(1) {

	    //if array has only two elements, second index is the pivot.
	    if(end == start + 1)
		return end;

	    //middle index...
	    auto mid = (start + end) / 2;

	    //if first array is not rotated...
	    if(nums[start] < nums[mid]) {

		//search second array.
		start = mid;

	    } else {

		//search first array.
		end = mid;

	    }
	}
    }

    public:
    int search(std::vector<int>& nums, int target) {

	if(nums.size() == 1) {
	    if(nums[0] == target)
		return 0;
	    return -1;
	}

	//find pivot index.
	auto pivotIndex = findPivot(nums);

	//non-rotated array.
	if(!pivotIndex) {

	    //if target is in range...
	    if(target >= nums[0] && target <= nums[nums.size() - 1])
		return binarySearch(nums, 0, nums.size() - 1, target);

	    //taret out of range.
	    return -1;
	}

	//rotated array.

	//if target is in first array range...
	if(target <= nums[pivotIndex - 1] && target >= nums[0])
	    return binarySearch(nums, 0, pivotIndex - 1, target);

	//if target is in second array range...
	if(target >= nums[pivotIndex] && target <= nums[nums.size() - 1])
	    return binarySearch(nums, pivotIndex, nums.size() - 1, target);

	//target out of range.
	return -1;
    }
};

int main() {
    std::vector<int> v = {0,1};

    for(auto e: v)
	std::cout << e << ' ';
    std::cout << '\n';

    Solution s;

    std::cout << "Search what: ";
    int n;
    std::cin >> n;
    auto l = s.search(v, n);
    std::cout << l << '\n';
}
