#include <iostream>

/*
   Populating Next Right Pointers in Each Node

   You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

   struct Node {
   int val;
   Node *left;
   Node *right;
   Node *next;
   }
   Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

   Initially, all next pointers are set to NULL.



   Example 1:
Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like 
in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

Example 2:
Input: root = []
Output: []


Constraints:

The number of nodes in the tree is in the range [0, 212 - 1].
-1000 <= Node.val <= 1000


Follow-up:

You may only use constant extra space.
The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.

Solution: Recursive approach.
	Connecting the next for the left child to right is trivial. Challenge lies in connecting the next of right
	child to the right sub tree node of same level.

	In each recursive call
	a. First well connect the left child's next to the right child.
	b. Then, inside a loop
		i. we'll connect left child's right child's next to the right child's left child.
		ii. we'll connect left child's right child's right child's next to the right child's left child's left child
			and so on for the full depth. This takes care of connecting left subtree node's next to the
			right subtree node at the same level
	c. We'll do recursive call on the root's left child
	d. We'll do recursive call on the root's right child
 */

class Node {
    public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
	    : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
    public:
	Node* connect(Node* root) 
	{
	    if(!root)
		return nullptr;

	    auto focusl{ root->left };
	    auto focusr{ root->right };
	    if(focusl)
		focusl->next = focusr;
	    while(focusl && focusr)
	    {
		focusl = focusl->right;
		focusr = focusr->left;
		if(focusl)
		    focusl->next = focusr;
	    }
	    connect(root->left);
	    connect(root->right);
	    return root;
	}
};

int main()
{
}

