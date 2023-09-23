#include <iostream>
#include <vector>
#include <stack>
#include <queue>

/*
   Construct Binary Tree from Inorder and Postorder Traversal

   Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

Example 1:


Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]


Constraints:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.
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
	TreeNode* assembleTree(const std::vector<int>& inorder, const std::vector<int>& postorder, int istart, int pstart, int size, int subTree, TreeNode* parent)
	{
	    auto iend{ istart + size - 1 };
	    auto pend{ pstart + size - 1 };
	    auto rootValue{ postorder[pend] };
	    auto root{ new TreeNode { rootValue } };
	    static int ctr{ };

	    /*
	       std::cout << "Ctr: " << ++ctr;
	       if(parent)
	       std::cout << ", parent: " << parent->val << ", ";
	       else
	       std::cout << ", parent: " << 'n' << ", ";
	       std::cout << "istart: " << istart << ", iend: " << iend;
	       std::cout << ", pstart: " << pstart << ", pend: " << pend << ", stree: " << subTree;
	       std::cout << ", rootVal: " << rootValue << ", size: " << size;
	       std::cout << ", rootAddr: " << root << '\n';
	       char ch;
	    //std::cin >> ch;
	     */

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
		//std::cout << "a return from ctr: " << ctr << '\n';
		return root;
	    }

	    for(auto i{ istart }; i <= iend; ++i)
	    {
		int j = i - istart;
		//std::cout << "\tsearching at " << i << '\n';
		if(inorder[i] == rootValue)
		{
		    if(i > istart)
		    {
			assembleTree(inorder, postorder, istart, pstart, i - istart, -1, root);
		    }
		    if(i < iend)
		    {
			assembleTree(inorder, postorder, i + 1, pstart + i - istart, size - i + istart - 1, 1, root);
		    }
		    break;
		}
	    }
	    //std::cout << "b return from ctr: " << ctr << '\n';
	    return root;
	}

	TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
	    return assembleTree(inorder, postorder, 0, 0, inorder.size(), 0, nullptr);
	}
};


int main()
{
    Solution s;
    //std::vector<int> inorder{6,5,7,4,2,1,9,3,8};
    //std::vector<int> postorder{6,7,5,4,2,9,8,3,1};

    //std::vector<int> inorder{4,2,5,1,3,7};
    //std::vector<int> postorder{4,5,2,7,3,1};

    std::vector<int> inorder{2};
    std::vector<int> postorder{2};

    TreeNode n1{ *(s.buildTree(inorder,postorder)) };
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
