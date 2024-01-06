#include <iostream>
#include <vector>
#include <queue>

/*
   Flood Fill

   An image is represented by an m x n integer grid image where image[i][j] 
   represents the pixel value of the image.

   You are also given three integers sr, sc, and color. You should perform 
   a flood fill on the image starting from the pixel image[sr][sc].

   To perform a flood fill, consider the starting pixel, plus any pixels 
   connected 4-directionally to the starting pixel of the same color as the 
   starting pixel, plus any pixels connected 4-directionally to those pixels 
   (also with the same color), and so on. Replace the color of all of the 
   aforementioned pixels with color.

   Return the modified image after performing the flood fill.


   Example 1

   Input 
   image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
   Output
   [[2,2,2],[2,2,0],[2,0,1]]
   Explanation - From the center of the image with position 
   (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected 
   by a path of the same color as the starting pixel (i.e., the 
   blue pixels) are colored with the new color.
   Note the bottom corner is not colored 2, because it is not 
   4-directionally connected to the starting pixel.

   Example 2

   Input
   image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
   Output
   [[0,0,0],[0,0,0]]
   Explanation - The starting pixel is already colored 0, so no 
   changes are made to the image.


   Constraints

   m == image.length
   n == image[i].length
   1 <= m, n <= 50
   0 <= image[i][j], color < 216
   0 <= sr < m
   0 <= sc < n

   Solution - O(n)
   We traverse from the given pixel breadth first and color connected elements. 
   We start at the given pixel by queing it into a traversal queue and start 
   traversing. If the current pixel (that we've traversed into) isn't already 
   colored (if it is, we deque and continue because otherwise we'll be locked 
   into a loop), we'll queue connected pixels. We'll color the current pixel, 
   deque current pixel and continue.

   See code and comments.
 */

class Solution {
    public:
	std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int color) {

	    //redundancy check.
	    if(color == image[sr][sc])
		return image;

	    //queue for breadth traversal.
	    std::queue<std::pair<int, int>> trav_q;

	    //start with the first pixel.
	    trav_q.push(std::make_pair(sr, sc));

	    //start traversal
	    while(!trav_q.empty()) {

		//current pixel's coordinates.
		int row = trav_q.front().first;
		int col = trav_q.front().second;

		//current pixel's color.
		int clr = image[row][col];

		//visited pixel. Ignore.
		if(clr == color) {
		    trav_q.pop();
		    continue;
		}

		//push connected pixels to queue.

		//top pixel.
		if(row > 0) {
		    //check if the pixel has same value.
		    if(image[row - 1][col] == clr)
			trav_q.push(std::make_pair(row - 1, col));
		}

		//bottom pixel.
		if(row < image.size() - 1) {
		    //check if the pixel has same value.
		    if(image[row + 1][col] == clr)
			trav_q.push(std::make_pair(row + 1, col));
		}

		//left pixel.
		if(col > 0) {
		    //check if the pixel has same value.
		    if(image[row][col - 1] == clr)
			trav_q.push(std::make_pair(row, col - 1));
		}

		//right pixel.
		if(col < image[0].size() - 1) {
		    //check if the pixel has same value.
		    if(image[row][col + 1] == clr)
			trav_q.push(std::make_pair(row, col + 1));
		}

		//replace current pixel's color.
		image[row][col] = color;

		//deque.
		trav_q.pop();
	    }

	    return image;
	}
};


int main() {
    Solution s;

    std::vector<std::vector<int>> image = {
	{1,0,1,1,1},
	{1,0,1,0,0},
	{1,1,1,1,1},
	{0,0,1,0,1},
	{1,1,1,0,1},
    };

    auto res = s.floodFill(image, 0, 0, 2);
}
