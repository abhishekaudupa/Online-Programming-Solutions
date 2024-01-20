#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

/*
   Sort an Array

   Given an array of integers nums, sort the array in ascending order and return it.

   You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.



   Example 1:

   Input- nums = [5,2,3,1]
   Output- [1,2,3,5]
   Explanation- After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
   Example 2:

   Input- nums = [5,1,1,2,0,0]
   Output- [0,0,1,1,2,5]
   Explanation- Note that the values of nums are not necessairly unique.


   Constraints-

   1 <= nums.length <= 5 * 104
   -5 * 104 <= nums[i] <= 5 * 104

   Solution - O(n log n) - Merge sort (using queue for merging).
 */

class Solution {
    using Vector = std::vector<int>;

    //queue for sorted array merging.
    std::queue<int> q;

    public:

    //merge sort function.
    void mergeSort(const int begin, const int end, Vector& source) {

	//base case, array size 1: just return.
	if(begin == end)
	    return;

	//base case, array size 2: rearrange in ascending order.
	if(end - begin == 1) {
	    if(source[begin] > source[end])
		std::swap(source[begin], source[end]);
	    return;
	}

	//half array start indices.
	auto i = begin;
	auto j = (begin + end) / 2 + 1;

	//recursive function call.
	mergeSort(i, j - 1, source);
	mergeSort(j, end, source);

	//array bifurcation complete. Start merging.
	//we'll be using a queue instead of auxiliary array to do
	//the merging.

	//traverse through both arrays.
	while((i <= (begin + end) / 2)) {

	    //if an element from second array is to be put in the first.
	    if(source[j] < source[i]) {

		//save the current element in the first array.
		q.push(source[i]);

		//put the replacement element in its place. Increment indices.
		source[i++] = source[j++];

		//break out of loop.
		break;
	    } else {

		//otherwise goto next element.
		++i;
	    }
	}

	//from this point, we'll make comparisons with the front element of queue (which has
	//elements from the 1st array).

	//while we still have elements in second array and filling up 1st array...
	while(!q.empty() && j <= end && i <= (begin + end) / 2) {

	    //push current element in 1st array to queue.
	    q.push(source[i]);

	    //if element in second array is smaller...
	    if(source[j] < q.front()) {
		//replace the element in 1st array with it.
		source[i++] = source[j++];
	    } else {
		//replce the element in 1st array with queue element.
		source[i++] = q.front();
		q.pop();
	    }
	}

	//while we still have elements in second array and filled up 1st array...
	while(!q.empty() && j <= end && i > (begin + end) / 2) {

	    //if element in second array is smaller...
	    if(source[j] < q.front()) {
		//replace the element in 1st array with it.
		source[i++] = source[j++];
	    } else {
		//replce the element in 1st array with queue element.
		source[i++] = q.front();
		q.pop();
	    }
	}

	//while we dont have elements in second array but still filling up 1st array...
	while(!q.empty() && i <= (begin + end) / 2) {
	    //enqueue the current element in 1st array.
	    q.push(source[i]);

	    //deque element from queue to current element.
	    source[i++] = q.front();
	    q.pop();
	}

	//dequeue rest of the elements...
	while(!q.empty()) {
	    source[i++] = q.front();
	    q.pop();
	}
    }

    std::vector<int> sortArray(std::vector<int>& nums) {
	mergeSort(0, nums.size() - 1, nums);
	return nums;
    }
};

int main() {
    std::vector<int> v = {1,1,5,0,0,2};

    std::cout << "Vector is ";
    for(auto& ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';

    Solution s;
    auto a = s.sortArray(v);

    std::cout << "Vector final is ";
    for(auto& ele: a)
	std::cout << ele << ' ';
    std::cout << '\n';
}
