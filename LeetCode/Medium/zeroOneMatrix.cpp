#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

/*
   01 Matrix

   Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

   The distance between two adjacent cells is 1.

   Example 1


   Input mat = [[0,0,0],[0,1,0],[0,0,0]]
   Output [[0,0,0],[0,1,0],[0,0,0]]
   Example 2


   Input mat = [[0,0,0],[0,1,0],[1,1,1]]
   Output [[0,0,0],[0,1,0],[1,2,1]]


   Constraints

   m == mat.length
   n == mat[i].length
   1 <= m, n <= 104
   1 <= m * n <= 104
   mat[i][j] is either 0 or 1.
   There is at least one 0 in mat.

   Solution - O(n).
   Idea is to first traverse the matrix and note all 0s. We'll start spreading out 
   in layers from those zeroes: 1s adjacent to these zeroes are at a distance 1. 1s 
   that are adjacent to the previous layer of ones are at a distance of 2 from the 
   nearest 0 and so on...

   This can be vastly improved though...
 */

class Solution {
    public:
	using coord_t = std::pair<int, int>;

	inline void mark_next_layer(std::queue<coord_t>& trav_q, 
		std::unordered_set<int*>& marked, 
		std::vector<std::vector<int>>& mat,
		coord_t& next,
		coord_t& curr) {

	    //if the next element is not in the 'marked' list...
	    if(marked.find(&(mat[next.first][next.second])) == marked.end()) {

		//increment it's value by 1, w.r.t to current value.
		mat[next.first][next.second] = mat[curr.first][curr.second] + 1;

		//push it to traversal queue.
		trav_q.push(next);

		//add it to the 'marked' list.
		marked.insert(&(mat[next.first][next.second]));
	    }
	}

	std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {

	    //breadth traversal queue.
	    std::queue<coord_t> trav_q;

	    //set to track to-visit elements.
	    std::unordered_set<int*> marked;

	    //push all 0s to traversal queue and mark them.
	    for(int i = 0; i < mat.size(); ++i) {
		for(int j = 0; j < mat[0].size(); ++j) {
		    if(mat[i][j] == 0) {
			auto coord = std::make_pair(i, j);
			trav_q.push(coord);
			marked.insert(&(mat[i][j]));
		    }
		}
	    }

	    //start traversal and mark all 1s adjacent to 0s.
	    while(!trav_q.empty()) {

		//current element's row and col.
		auto curr_row = trav_q.front().first;
		auto curr_col = trav_q.front().second;

		//increment elements in the next layer, add them to traversal queue.

		//top element.
		if(curr_row > 0) {
		    auto coord = std::make_pair(curr_row - 1, curr_col);
		    mark_next_layer(trav_q, marked, mat, coord, trav_q.front());
		}

		//bottom element.
		if(curr_row < mat.size() - 1) {
		    auto coord = std::make_pair(curr_row + 1, curr_col);
		    mark_next_layer(trav_q, marked, mat, coord, trav_q.front());
		}

		//left element.
		if(curr_col > 0) {
		    auto coord = std::make_pair(curr_row, curr_col - 1);
		    mark_next_layer(trav_q, marked, mat, coord, trav_q.front());
		}

		//left element.
		if(curr_col < mat[0].size() - 1) {
		    auto coord = std::make_pair(curr_row, curr_col + 1);
		    mark_next_layer(trav_q, marked, mat, coord, trav_q.front());
		}

		//deque.
		trav_q.pop();
	    }
	    return mat;
	}
};

int main() {

    std::vector<std::vector<int>> matrix = {
	{1,1,1,1,0},
	{0,1,1,1,1},
	{1,1,1,1,1},
	{1,1,1,1,1},
	{1,1,1,0,1}
    };

    Solution s;
    s.updateMatrix(matrix);
}

