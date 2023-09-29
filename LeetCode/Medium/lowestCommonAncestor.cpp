#include <iostream>
#include <deque>
#include <stack>
#include <queue>
#include <deque>

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
	During each recursion, we'll push the root into two double ended ques (say dq_p and dq_q).
	These queues represent the path for both nodes p and q from the root node. Once we find
	p, we stop pushing nodes into the dq_p and the same goes for node q. Once both nodes are
	found we stop searching.

	Now we compare elements in both queues and see at what node they start to differ. The node
	before the difference shows up is the LCA node.

	This solution is better than the previous one (see previous commit).
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
	std::deque<TreeNode*> s_p;
	std::deque<TreeNode*> s_q;
	bool p_found{ false }, q_found{ false };

	void preOrderSearch(TreeNode* root, TreeNode* p, TreeNode* q)
	{
	    if(p_found && q_found)
		return;

	    if(!p_found)
		s_p.push_back(root);

	    if(!q_found)
		s_q.push_back(root);

	    if(root->val == p->val)
		p_found = true;

	    if(root->val == q->val)
		q_found = true;

	    if(root->left)
		preOrderSearch(root->left, p, q);

	    if(root->right && !(p_found && q_found))
		preOrderSearch(root->right, p, q);

	    if(!p_found)
		s_p.pop_back();

	    if(!q_found)
		s_q.pop_back();
	}

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
	    if(p == root)
		return root;

	    if(q == root)
		return root;

	    preOrderSearch(root, p, q);

	    auto lca{ root };

	    while(!s_q.empty() && !s_p.empty())
	    {
		if(s_q.front() == s_p.front())
		{
		    lca = s_q.front();
		    s_q.pop_front();
		    s_p.pop_front();
		}
		else
		{
		    break;
		}
	    }

	    return lca;
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
    auto lca{ s.lowestCommonAncestor(&n3, &n6, &n2) };
    std::cout << "LCA of node 6 and 2 is " << lca->val << '\n';
}

