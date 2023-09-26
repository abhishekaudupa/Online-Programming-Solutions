#include <iostream>
#include <vector>
#include <stack>
#include <queue>

/*
   Construct Binary Tree from Preorder and Inorder Traversal

   Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.



   Example 1:
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.

Solution: Recursive approach. Each time, a sub interval of the inorder and preorder vector is sent into the function (the indices are sent, not a new sub vector)
	During each recursion
	1. Root element is found as the first element of the preorder vector
	2. This element is searched for in the inorder vector
	3. Elements to the left of the root elem. in the inorder vector form the left subtree and those to the right of the root element
		form the right subtree (if they exist, respectively, which is easy to check. See code).
	4. First, left subtree is constructed and then the right subtree is constructed. To do that
		a. Send the indices of LST in the inorder and preorder vectors along with the size of the LST sub-vector
		b. Same as above for the RST. See code for the formulae.
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

class Solution {
    public:
	TreeNode* assembleTree(const std::vector<int>& inorder, const std::vector<int>& preorder, int istart, int pstart, int size, int subTree, TreeNode* parent)
	{
	    auto iend{ istart + size - 1 };
	    auto pend{ pstart + size - 1 };
	    auto rootValue{ preorder[pstart] };
	    auto root{ new TreeNode { rootValue } };

	    if(parent)
	    {
		switch(subTree)
		{
		    case -1:
			parent->left = root;
			break;
		    case 1:
			parent->right = root;
			break;
		}
	    }

	    if(size == 1)
	    {
		return root;
	    }

	    for(auto i{ istart }; i <= iend; ++i)
	    {
		if(inorder[i] == rootValue)
		{
		    if(i > istart)
		    {
			assembleTree(inorder, preorder, istart, pstart + 1, i - istart, -1, root);
		    }
		    if(i < iend)
		    {
			assembleTree(inorder, preorder, i + 1, pstart + 1 + i - istart, size - i + istart - 1, 1, root);
		    }
		    break;
		}
	    }
	    return root;
	}

	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
	    return assembleTree(inorder, preorder, 0, 0, inorder.size(), 0, nullptr);
	}
};


int main()
{
    Solution s;

    std::vector<int> inorder{9,3,15,20,7};
    std::vector<int> preorder{3,9,20,15,7};

    TreeNode n1{ *(s.buildTree(preorder, inorder)) };
    TreeNode n2{ 2 };
    TreeNode n3{ 3 };
    TreeNode n4{ 4 };
    TreeNode n5{ 5 };
    TreeNode n6{ 6 };
    TreeNode n7{ 7 };
    TreeNode n8{ 8 };
    TreeNode n9{ 9 };

    /*
       n1.left = &n2;
       n1.right = &n3;
       n2.left = &n4;
       n3.left = &n9;
       n3.right = &n8;
       n4.right = &n5;
       n5.left = &n6;
       n5.right = &n7;
     */

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
