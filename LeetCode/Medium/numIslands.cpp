#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <queue>

/*
   Number of Islands
   Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

   An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

   Example 1:
Input: grid = 
[
["1","1","1","1","0"],
["1","1","0","1","0"],
["1","1","0","0","0"],
["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = 
[
["1","1","0","0","0"],
["1","1","0","0","0"],
["0","0","1","0","0"],
["0","0","0","1","1"]
]
Output: 3


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.

Solution 1:
	We traverse through the matrix and find a piece of land (a '1' at index i,j), then we 'walk'
	about the land and until we find it's borders. Now we've found 1 island. Repeat this for all
	elements of the matrix. While we do this, we keep track of the 'patches of land' that we've
	already visited.

	Implementation:
	1. We initialize a queue to keep track of the index of 'lands'.
	2. We initialize an unordered set to keep track of 'patches of land' we've visited.
	3. We traverse through the matrix using two for loops (one for row and another for column).
	4. If we land on a 'patch of land' that hasn't already been visited (aka not in the unord. set)
		i. We visit the neighbouring 'patches of land' using BFS (using a queue).
		ii. Put the visited 'patches of land' into the set (so that we keep track of visited patches).
		iii. At the end of the BFS, we've 'found' and 'island'. Increment the counter by 1.
	5. Return the counter.

Solution 2 (Faster):
	Same as above except, we don't use the unordered set to keep track of the visited patches of land.
	We 'take a dump' on the patch of land we visited during BFS to mark our visit.

	Implementation:
	Same as above, except, during BFS, we change the '1' to a '#' (or anything else) so that we know
	we've visited it.
 */

class Solution {
    public:
	int numIslands(std::vector<std::vector<char>>& grid) 
	{
	    auto row_count{ grid.size() };
	    auto col_count{ grid[0].size() };
	    int island_count{};
	    std::queue<std::pair<unsigned int, unsigned int>> q;

	    for(auto i{ 0u }; i < row_count; ++i)
	    {
		for(auto j{ 0u }; j < col_count; ++j)
		{
		    if(grid[i][j] == '1')
		    {
			q.push({i, j});
			while(!q.empty())
			{
			    auto ele{ q.front() };
			    auto x{ ele.first };
			    auto y{ ele.second };
			    grid[x][y] = '#';

			    if(y > 0 && (grid[x][y - 1] == '1'))	//push left node
			    {
				q.push({ x, y - 1 });
				grid[x][y - 1] = '#';
			    }

			    if(y < col_count - 1 && (grid[x][y + 1] == '1'))	//push right node
			    {
				q.push({ x, y + 1 });
				grid[x][y + 1] = '#';
			    }

			    if(x > 0 && (grid[x - 1][y] == '1'))	//push top node
			    {
				q.push({ x - 1, y });
				grid[x - 1][y] = '#';
			    }

			    if(x < row_count - 1 && (grid[x + 1][y] == '1'))	//push bottom node
			    {
				q.push({ x + 1, y });
				grid[x + 1][y] = '#';
			    }

			    q.pop();
			}
			++island_count;
		    }
		}
	    }

	    return island_count;
	}
};

int main()
{
    std::vector<std::vector<char>> v
    {
	{'1','1','0','1','0','1'},
	    {'1','0','1','1','0','0'},
	    {'0','0','1','1','0','1'},
	    {'1','0','1','0','1','1'},
	    {'0','0','1','1','0','1'},
	    {'1','1','1','0','1','1'},
    };

    Solution s;
    std::cout << s.numIslands(v) << '\n';
}

