#include <iostream>
#include <bitset>

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
	We'll have a pathCodec to that records the path of the node to be found (I'm using
	a bitset of 10000 bits, with 1 indicating a left node and 0 indicating a right node,
	root node is 0). We'll compare the path coded of both nodes and the node at which 
	the path codec starts to differ is the LCA node.

	This idea doesn't look very efficient. I've got a better idea. See the other commit.
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
	std::bitset<10001> pathCodec_p;
	std::bitset<10001> pathCodec_q;
	int level_p{};
	int level_q{};

	void preOrderSearch(TreeNode* root, TreeNode* p, TreeNode* q, int level, std::bitset<10001> pathCodec)
	{
	    if(level_p && level_q)
		return;

	    if(root->val == p->val)
	    {
		level_p = level;
		pathCodec_p = pathCodec;
	    }

	    if(root->val == q->val)
	    {
		level_q = level;
		pathCodec_q = pathCodec;
	    }

	    if(root->left)
	    {
		preOrderSearch(root->left, p, q, level + 1, ((pathCodec << 1) | std::bitset<10001>(1)));
	    }

	    if(root->right)
	    {
		preOrderSearch(root->right, p, q, level + 1, pathCodec << 1);
	    }
	}

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	    if(p == root)
		return root;

	    if(q == root)
		return root;

	    preOrderSearch(root, p, q, 0, 0);

	    int i{};
	    auto lca{ root };
	    while(1)
	    {
		if((level_p - i - 1 >= 0) && (level_q - i -1 >= 0))
		{
		    auto dir_p{ (pathCodec_p >> (level_p - i - 1)) & std::bitset<10001>(1) };
		    auto dir_q{ (pathCodec_q >> (level_q - i - 1)) & std::bitset<10001>(1) };
		    if(dir_p == dir_q)
		    {
			if(dir_p[0])
			    lca = lca->left;
			else
			    lca = lca->right;
		    }
		    else
			return lca;
		    ++i;
		}
		else
		{
		    return lca;
		}
	    }
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
    auto lca{ s.lowestCommonAncestor(&n3, &n4, &n6) };
    std::cout << "LCA of node 6 and 4 is " << lca->val << '\n';
}

