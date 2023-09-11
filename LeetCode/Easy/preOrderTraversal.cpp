#include <iostream>
#include <vector>
#include <stack>

/*
   	Binary Tree Preorder Traversal
	https://leetcode.com/explore/learn/card/data-structure-tree/134/traverse-a-tree/928/

Given the root of a binary tree, return the preorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]


Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100


Follow up: Recursive solution is trivial, could you do it iteratively?

Solution:
	1. Recursive and iterative. Code is self explanatory.
 */

//#define RECURSIVE

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#ifdef RECURSIVE
std::vector<int> preorderTraversal(TreeNode* root) {	//recursive pre order traversal
    static std::vector<int> v;	//static usage will not work in Leetcode
    if(root)
    {
	v.push_back(root->val);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
    }
    return v;
}

#else
std::vector<int> preorderTraversal(TreeNode* root) {	//iterative pre order traversal
    std::vector<int> v;
    if(!root)
	return v;
    std::stack<TreeNode*> travStack;
    travStack.push(root);

    while(!travStack.empty())
    {
	auto temp{ travStack.top() };
	v.push_back(temp->val);
	travStack.pop();
	if(temp->right)
	    travStack.push(temp->right);
	if(temp->left)
	    travStack.push(temp->left);
    }

    return v;
}
#endif

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

    n1.left = &n2;
    n1.right = &n4;
    n2.left = &n3;

    std::vector<int> v{ preorderTraversal(&n1) };
    for(const auto ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';
}

