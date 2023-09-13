#include <iostream>
#include <vector>
#include <stack>

/*
   Binary Tree Postorder Traversal

   Given the root of a binary tree, return the postorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]


Constraints:

The number of the nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100


Follow up: Recursive solution is trivial, could you do it iteratively?

Solution:
	Iterative traversal. Code self explanatory.
 */


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

std::vector<int> postorderTraversal(TreeNode* root) {	//iterative in order traversal
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
	else if(st.top()->right)
	{
	    st.push(st.top()->right);
	}
	else
	{
	    while(!st.empty())
	    {
		//std::cout << "stuck\n";
		v.push_back(st.top()->val);
		auto temp{ st.top() };
		st.pop();
		if(!st.empty())
		{
		    if(st.top()->right)
		    {
			if(st.top()->right != temp)
			{
			    st.push(st.top()->right);
			    break;
			}
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
    TreeNode n9{ 9 };

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n3.left = &n9;
    n3.right = &n8;
    n4.right = &n5;
    n5.left = &n6;
    n5.right = &n7;


    std::vector<int> v{ postorderTraversal(&n1) };
    for(const auto ele: v)
	std::cout << ele << ' ';
    std::cout << '\n';
}

