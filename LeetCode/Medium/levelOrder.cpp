#include <iostream>
#include <vector>
#include <queue>

/*
   Binary Tree Level Order Traversal

   Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000

Solution:
	Iterative traversal using queue. Code self explanatory. 

 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> v;
    if(!root)
	return v;

    std::queue<TreeNode*> q;
    q.push(root);
    int ctrp{ 1 }, ctrn{ 0 };
    while(!q.empty())
    {
	std::vector<int> vi;
	for(auto i{ 0 }; i < ctrp; ++i)
	{
	    if(q.front()->left)
	    {
		q.push(q.front()->left);
		++ctrn;
	    }
	    if(q.front()->right)
	    {
		q.push(q.front()->right);
		++ctrn;
	    }
	    vi.push_back(q.front()->val);
	    q.pop();
	}
	ctrp = ctrn;
	ctrn = 0;
	v.push_back(vi);
    }
    return v;
}

int main()
{
    TreeNode n1{ 1 };
    TreeNode n2{ 2 };
    TreeNode n3{ 3 };
    TreeNode n4{ 4 };
    TreeNode n5{ 5 };
    TreeNode n6{ 6 };
    TreeNode n7{ 7 };
    TreeNode n8{ 8 };
    TreeNode n9{ 9 };

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n3.left = &n9;
    n3.right = &n8;
    n4.right = &n5;
    n5.left = &n6;
    n5.right = &n7;

    auto v{ levelOrder(&n1) };
    for(const auto& ele: v)
    {
	std::cout << '{';
	for(auto i{ 0 }; i < ele.size(); ++i)
	{
	    if(i != 0)
		std::cout << ' ';
	    std::cout << ele[i];
	}
	std::cout << "} ";
    }
    std::cout << '\n';
}

