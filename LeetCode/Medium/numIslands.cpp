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
 */

class Solution {
    public:
	int numIslands(std::vector<std::vector<char>>& grid) 
	{
	    auto row_count{ grid.size() };
	    auto col_count{ grid[0].size() };
	    int island_count{};
	    std::queue<std::pair<unsigned int, unsigned int>> q;
	    std::unordered_set<char*> visited;

	    for(auto i{ 0u }; i < row_count; ++i)
	    {
		for(auto j{ 0u }; j < col_count; ++j)
		{
		    if(grid[i][j] == '1' && visited.find(&grid[i][j]) == visited.end())
		    {
			q.push({i, j});
			visited.insert(&grid[i][j]);
			while(!q.empty())
			{
			    auto ele{ q.front() };
			    auto x{ ele.first };
			    auto y{ ele.second };
			    if(y > 0 && (grid[x][y - 1] == '1') && (visited.find(&grid[x][y - 1]) == visited.end()))	//push left node
			    {
				q.push({ x, y - 1 });
				visited.insert(&grid[x][y - 1]);
			    }

			    if(y < col_count - 1 && (grid[x][y + 1] == '1') && (visited.find(&grid[x][y + 1]) == visited.end()))	//push right node
			    {
				    q.push({ x, y + 1 });
				    visited.insert(&grid[x][y + 1]);
			    }

			    if(x > 0 && (grid[x - 1][y] == '1') && visited.find(&grid[x - 1][y]) == visited.end())	//push top node
			    {
				    q.push({ x - 1, y });
				    visited.insert(&grid[x - 1][y]);
			    }

			    if(x < row_count - 1 && (grid[x + 1][y] == '1') && visited.find(&grid[x + 1][y]) == visited.end())	//push bottom node
			    {
				    q.push({ x + 1, y });
				    visited.insert(&grid[x + 1][y]);
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

