#include<iostream>

/*
   Search in a Binary Search Tree

   You are given the root of a binary search tree (BST) and an integer val.

   Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

   Example 1:

   Input- root = [4,2,7,1,3], val = 2
   Output- [2,1,3]

   Example 2:

   Input- root = [4,2,7,1,3], val = 5
   Output- []

   Constraints-

   The number of nodes in the tree is in the range [1, 5000].
   1 <= Node.val <= 107
   root is a binary search tree.
   1 <= val <= 107

   Solution - O(n). Code self explanatory.
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
	TreeNode* searchBST(TreeNode* root, int val) {
	    if(!root)
		return NULL;

	    if(root->val == val) {
		return root;
	    }

	    if(val < root->val)
		return searchBST(root->left, val);
	    else
		return searchBST(root->right, val);
	}
};

int main() {
    TreeNode n4 = {4, NULL, NULL};
    TreeNode n2 = {2, NULL, NULL};
    TreeNode n7 = {7, NULL, NULL};
    TreeNode n1 = {1, NULL, NULL};
    TreeNode n3 = {3, NULL, NULL};

    n4.left = &n2;
    n4.right = &n7;

    n2.left = &n1;
    n2.right = &n3;

    TreeNode *root = &n4;

    Solution s;
    auto ans = s.searchBST(root, 3);

    std::cout << (ans? ans->val : 0);
    std::cout << '\n';
}

