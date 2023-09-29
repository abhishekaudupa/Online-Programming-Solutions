#include <iostream>

/*
   Lowest Common Ancestor of a Binary Tree

   Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

   According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between 
   two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a 
   node to be a descendant of itself).”

   Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to 
the LCA definition.

Example 3:
Input: root = [1,2], p = 1, q = 2
Output: 1

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the tree.

Solution: Recursive
	We do a depth first search (pre-order in this case, others would do just as well).

	The concept: if we're given a root and p and q are found on the LST (or RST) and
	RST (or LST) of the root, then LCA is the root itself.

	Code is self-explanatory
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
	bool p_found{ false }, q_found{ false };

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
	    if(p == root)
	    {
		p_found = true;
		return root;
	    }

	    if(q == root)
	    {
		q_found = true;
		return root;
	    }

	    if(!root)
		return root;

	    if(p_found && q_found)
		return nullptr;

	    auto a { lowestCommonAncestor(root->left, p, q) };
	    auto b { lowestCommonAncestor(root->right, p, q) };

	    if(a && b)
		return root;
	    else if(a)
		return a;
	    else
		return b;
	}
};

int main()
{
    TreeNode n3{ 3 };
    TreeNode n5{ 5 };
    TreeNode n1{ 1 };
    TreeNode n6{ 6 };
    TreeNode n2{ 2 };
    TreeNode n0{ 0 };
    TreeNode n8{ 8 };
    TreeNode n7{ 7 };
    TreeNode n4{ 4 };

    n3.left = &n5;
    n3.right = &n1;
    n5.left = &n6;
    n5.right = &n2;
    n1.left = &n0;
    n1.right = &n8;
    n2.left = &n7;
    n2.right = &n4;

    Solution s;
    auto lca{ s.lowestCommonAncestor(&n3, &n7, &n6) };
    std::cout << "LCA of node 7 and 6 is " << lca->val << '\n';
}

