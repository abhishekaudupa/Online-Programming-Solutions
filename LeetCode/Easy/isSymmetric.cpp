#include <iostream>
#include <vector>
#include <deque>
/*
   Symmetric Tree

   Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

   Example 1:
Input: root = [1,2,2,3,4,4,3]
Output: true

Example 2:
Input: root = [1,2,2,null,3,null,3]
Output: false

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100


Follow up: Could you solve it both recursively and iteratively?
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void printdq(std::deque<TreeNode*> q)
{
    while(!q.empty())
    {
	if(q.front())
	    std::cout << q.front()->val << ' ';
	else
	    std::cout << "null ";
	q.pop_front();
    }
    std::cout << '\n';
}

/*
   Iterative Solution

   Algorithm Overview
   1. Start at the left subtree.
   2. Insert each child (L-R, level-wise) at the back of a queue
   3. Now start at the right subtree
   4. Insert each child (R-L, level-wise) at the front of the queue
   5. Check if the queue is symmetric about the center.

   */
bool isSymmetric(TreeNode* root) {
    std::deque<TreeNode*> dq, dqtemp;

    dq.push_back(root->left);
    while(!dq.empty())
    {
	if(dq.front())
	{
	    dq.push_back(dq.front()->left);
	    dq.push_back(dq.front()->right);
	    dqtemp.push_back(dq.front());
	    dq.pop_front();
	}
	else
	{
	    dqtemp.push_back(dq.front());
	    dq.pop_front();
	}
    }

    dq.push_back(root->right);
    while(!dq.empty())
    {
	if(dq.front())
	{
	    dq.push_back(dq.front()->right);
	    dq.push_back(dq.front()->left);
	    dqtemp.push_front(dq.front());
	    dq.pop_front();
	}
	else
	{
	    dqtemp.push_front(dq.front());
	    dq.pop_front();
	}
    }

    while(!dqtemp.empty())
    {
	if(dqtemp.front() && dqtemp.back())
	{
	    if(dqtemp.front()->val == dqtemp.back()->val)
	    {
		dqtemp.pop_front();
		dqtemp.pop_back();
	    }
	    else
		return false;
	}
	else
	{
	    if(dqtemp.front() || dqtemp.back())
		return false;
	    else
	    {
		dqtemp.pop_front();
		dqtemp.pop_back();
	    }
	}
    }
    return true;
}


int main()
{
    TreeNode n1{ 1 };
    TreeNode n2{ 2 };
    TreeNode n3{ 2 };
    TreeNode n4{ 3 };
    TreeNode n5{ 4 };
    TreeNode n6{ 4 };
    TreeNode n7{ 3 };
    TreeNode n8{ 8 };

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.left = &n6;
    n3.right = &n7;

    std::cout << isSymmetric(&n1) << '\n';

}
