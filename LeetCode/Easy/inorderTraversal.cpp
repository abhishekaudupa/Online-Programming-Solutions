#include <iostream>
#include <vector>
#include <stack>

/*
   Binary Tree Inorder Traversal

   Given the root of a binary tree, return the inorder traversal of its nodes' values.

   Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

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
	1. Iterative. Code self explanatory
 */


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

std::vector<int> inorderTraversal(TreeNode* root) {	//iterative in order traversal
    std::vector<int> v;
    if(!root)
	return v;
    std::stack<TreeNode*> st;
    st.push(root);

    while(!st.empty())
    {
	if(st.top()->left)
	{
	    st.push(st.top()->left);
	}
	else
	{
	    v.push_back(st.top()->val);
	    auto temp{ st.top() };
	    st.pop();

	    if(temp->right)
	    {
		st.push(temp->right);
	    }
	    else
	    {
		while(!st.empty())
		{
		    v.push_back(st.top()->val);
		    temp = st.top();
		    st.pop();
		    if(temp->right)
		    {
			st.push(temp->right);
			break;
		    }
		}
	    }
	}
    }

    return v;
}

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

    n1.right = &n2;
    //n1.right = &n4;
    n2.right = &n3;

    std::vector<int> v{ inorderTraversal(&n1) };
    for(const auto ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';
}

