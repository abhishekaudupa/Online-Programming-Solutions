#include <iostream>
#include <vector>

/*
   Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

   In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

   Example 1:

Input: rowIndex = 3
Output: [1,3,3,1]

Example 2:

Input: rowIndex = 0
Output: [1]

Example 3:

Input: rowIndex = 1
Output: [1,1]


Constraints:

0 <= rowIndex <= 33


Follow up: Could you optimize your algorithm to use only O(rowIndex) extra space?

Solution:
Each element is the binomial co-efficient in the pascal's triangle. Caluculate it. Done
 */

std::vector<int> getRow(int rowIndex) 
{
    std::vector<int> v(rowIndex + 1);
    unsigned long long res{ 1 };
    for(auto i{ 0 }; i <= rowIndex - i; ++i)
    {
	int n{ rowIndex };
	int r{ (i > n - i)? n - i: i };
	res = 1;
	for(auto i{ n - r + 1 }, j{ 1 }; i <= n; ++i, ++j)
	    res = (res * i) / j;
	v[i] = res;
	v[rowIndex - i] = res;
    }
    return v;
}

int main()
{
    char c{ 'Y' };
    while(c == 'Y')
    {
	std::cout << "Enter row index: ";
	int rowIndex;
	std::cin >> rowIndex;
	std::vector<int> v{ getRow(rowIndex) };

	for(const auto ele: v)
	    std::cout << ele << ' ';
	std::cout << '\n';

	std::cout << "Continue? Y/N: ";
	std::cin >> c;
    }
}

