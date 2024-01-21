#include <iostream>

/*
   Validate Binary Search Tree

   Given the root of a binary tree, determine if it is a valid binary search tree (BST).

   A valid BST is defined as follows:

   The left subtree of a node contains only nodes with keys less than the node's key.
   The right subtree of a node contains only nodes with keys greater than the node's key.
   Both the left and right subtrees must also be binary search trees.

   Example 1:

   Input- root = [2,1,3]
   Output- true

   Example 2:

   Input- root = [5,1,4,null,null,3,6]
   Output- false
   Explanation- The root node's value is 5 but its right child's value is 4.

   Constraints-

   The number of nodes in the tree is in the range [1, 104].
   -231 <= Node.val <= 231 - 1

   Solution - O(n).
   Inorder traversal and check order of elements during traversal.
   Code self-explanatory.
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

    //to keep track of traversal order.
    TreeNode *trav_node = NULL;

    public:

    //in-order traversal and check.
    bool isValidBST(TreeNode* root) {

	if(!root)
	    return true;

	//traverse to LST and check.
	if(!isValidBST(root->left))
	    return false;

	//if the trav_node is not NULL...
	if(!trav_node) {
	    //update the trav_node with current node.
	    trav_node = root;
	} else {
	    //if the current node is not in ascending order with trav_node...
	    if(trav_node->val >= root->val) {
		//this isn't a BST.
		return false;
	    }

	    //update trav_node with current node.
	    trav_node = root;
	}

	//traverse to RST and check.
	if(!isValidBST(root->right))
	    return false;

	//BST if we've reached here.
	return true;
    }
};

int main() {
    TreeNode n1 = {1, NULL, NULL};
    TreeNode n2 = {2, NULL, NULL};
    TreeNode n3 = {3, NULL, NULL};
    TreeNode n4 = {4, NULL, NULL};
    TreeNode n5 = {5, NULL, NULL};

    n3.left = &n1;
    n3.right = &n5;
    n5.left = &n2;
    n2.right = &n4;

    Solution s;
    auto val = s.isValidBST(&n3);

    if(val)
	std::cout << "Valid BST\n";
    else
	std::cout << "Not BST\n";
}
