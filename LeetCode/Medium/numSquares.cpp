#include <iostream>
#include <queue>

/*
   Perfect Squares

   Given an integer n, return the least number of perfect square numbers that sum to n.

   A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.



   Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.


Constraints:

1 <= n <= 104

Solution:
	This is a breadth first search solution and at the time of writing this, this is the best I could come up with.

	The idea is to first get the greatest number less than n, whose square 
	is less than or equal to n, i.e, to get floor(sqrt(n)). If n is a perfect
	square, we got the least number of perfect squares that sums to n - one.

	If n is not a perfect square, then things get spicy. We'd have to find all
	combinations of sums of perfect squares that sums up to n and choose the 
	combination which has least number of squares in it.

	To do this, we start with the floor(sqrt(n)) at the beginning and add other
	perfect squares to it until we reach n, while all the time we keep count of
	how many numbers we've added so far. To do this, we use a queue and we push
	a pair everytime to the queue. The pair has two numbers: the running sum and
	a count which tells how many perfect squares has led to that running sum.

	We start by pushing n with count 0 to the queue. We also init a minCount
	variable that is equal to n (because n is a sum of n 1s and 1 is a perfect
	square). Then we run a loop as long as the queue isn't empty. In it we do 
	the following:
		1. We get the current running sum and the count.
			- As an optimization (a necessary one at that), we'll check if
			  the current count is greater than or equal to one less than
			  the minCount. If it is, we pop the current element and move
			  on. This is because, in the best case, the current element
			  would lead us to n with an increment of 1 count which is equal
			  to minCount and that'd be useless to our search. So better
			  not bother with it.
		2. We calculate the balance which is the difference between running sum
		   and n.
		3. We get the floor(sqrt(balance)) whose square we'll add to the running
		   sum along with the count incremented by 1.
		   	- we'll also add all numbers below this number till 1, with the
			  count as above.
			- if we reach n while doing so, we'll see if the count is less
			  than minCount. If it is, we'll take this as the new minCount
			  and break the loop (an optimization because we don't need any 
			  more sums downstream because their count will then be greater
			  than minCount anyway).
		4. We pop the top element of the queue.

 */

class Solution {
    public:

	using SearchPair = std::pair<int, int>;
	using SearchQueue = std::queue<SearchPair>;

	inline int getFloorSqrt(int n) {
	    int i = 1;
	    for(; i * i <= n; ++i);
	    return --i;
	}

	int numSquares(int n) {

	    //n is a perfect square.
	    if(n == getFloorSqrt(n))
		return 1;

	    //minimum number of squares. At max it is n (1 * n).
	    int minCount = n;

	    //search element.
	    SearchPair sumAndCount;

	    //queue for breadth first search.
	    SearchQueue sumQ;

	    //push the first element: n, 0.
	    sumQ.push({n, 0});

	    //conduct BFS.
	    while(!sumQ.empty()) {

		//get the front element.
		auto curSum = sumQ.front().first;
		auto curCount = sumQ.front().second;

		//optimization.
		if(curCount >= minCount - 1) {
		    sumQ.pop();
		    continue;
		}

		//calculate the balance sum.
		auto balance = curCount? (n - curSum): curSum;

		//build the next element to push.
		auto next = getFloorSqrt(balance);
		auto nextCount = curCount + 1;

		while(next != 0) {

		    //calculate the next sum to push.
		    auto nextSum = curCount? (curSum + next * next): (next * next);

		    if(nextSum != n) {
			//push the next element, if it isn't equal to n.
			sumQ.push({nextSum, nextCount});
		    } else {
			//otherwise, store the count, if it's less than minCount.
			if(nextCount < minCount) {
			    minCount = nextCount;
			    break;
			}
		    }
		    --next;
		}

		//pop the queue.
		sumQ.pop();
	    }

	    return minCount;
	}
};

int main()
{
    Solution s;
    int n;
    std::cin >> n;
    int ct = s.numSquares(n);
    std::cout << "Min count is " << ct << '\n';
}
