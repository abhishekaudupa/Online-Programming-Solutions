#include <iostream>
#include <iomanip>
#include <vector>

/*
   Search a 2D Matrix II

   Write an efficient algorithm that searches for a value target in an m x n 
   integer matrix matrix. This matrix has the following properties:

   Integers in each row are sorted in ascending from left to right.
   Integers in each column are sorted in ascending from top to bottom.


   Example 1:

   Input- matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],
   [18,21,23,26,30]], target = 5
   Output- true

   Example 2:

   Input- matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],
   [18,21,23,26,30]], target = 20
   Output- false

   Constraints-

   m == matrix.length
   n == matrix[i].length
   1 <= n, m <= 300
   -10^9 <= matrix[i][j] <= 10^9
   All the integers in each row are sorted in ascending order.
   All the integers in each column are sorted in ascending order.
   -10^9 <= target <= 10^9

   Solution - O(sqrt(n)). Recursive.
   Search thru the diagonal till you find an element greater than target. When you 
   find one, search in the matrix above the current element and in the matrix to the 
   left of the element. If you reach the border of the matrix and haven't yet found 
   an element greater than taret, search in the matrix above or to the left of the 
   element. We're dividing the matrix in 4 during each call and searching in two of 
   them this way.
 */

class Solution {

    using IntMatrix = std::vector<std::vector<int>>;

    //element presence flag.
    bool found = false;

    public:

    void sM(IntMatrix& matrix, int rowF, int rowT, int colF, int colT, int target) {

	//abandon further search if element found.
	if(found)
	    return;

	//diagonal traversal indices.
	int i = rowF, j = colF;

	//traverse the diagonal.
	while(i <= rowT && j <= colT) {

	    //if the target matches the diagonal element...
	    if(matrix[i][j] == target) {
		found = true;
		return;
	    }

	    //if the target is smaller than a diagonal element...
	    if(matrix[i][j] > target) {

		//search in the matrix above the current diagonal element.
		if(i > rowF)
		    sM(matrix, rowF, i - 1, j, colT, target);

		//search in the matrix to the left of the current diagonal element.
		if(j > colF)
		    sM(matrix, i, rowT, colF, j - 1, target);

		//stop.
		return;
	    }

	    //proceed.
	    ++i, ++j;
	}

	//retract.
	--i, --j;

	//target larger than any diagonal element.

	//search in the matrix below the last diagonal element, if possible.
	if(i < rowT) {
	    sM(matrix, i + 1, rowT, colF, j, target);
	    return;
	}

	//search in the matrix to the right of the diagonal element, if possible.
	if(j < colT) {
	    sM(matrix, rowF, i, j + 1, colT, target);
	    return;
	}
    }

    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
	//call the search function.
	sM(matrix, 0, matrix.size() - 1, 0, matrix[0].size() - 1, target);

	//return the element presence flag.
	return found;
    }
};

int main() {

    using IntMatrix = std::vector<std::vector<int>>;

    IntMatrix m = {
	{1,4,7,11,15},
	{2,5,8,12,19},
	{3,6,9,16,22},
	{10,13,14,17,24},
	{18,21,23,26,30}
    };

    for(auto& v: m) {
	for(auto& e: v)
	    std::cout << std::setw(2) << std::setfill('0') << e << ' ';
	std::cout << '\n';
    }

    Solution s;
    std::cout << "Search what: ";
    int n;
    std::cin >> n;
    auto t = s.searchMatrix(m, n);
    if(t)
	std::cout << "found\n";
    else
	std::cout << "not found\n";
}
