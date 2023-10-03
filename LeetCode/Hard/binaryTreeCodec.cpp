#include <iostream>
#include <queue>
#include <string>

/*
   Serialize and Deserialize Binary Tree

   Serialization is the process of converting a data structure or object into a sequence of bits so 
   that it can be stored in a file or memory buffer, or transmitted across a network connection link 
   to be reconstructed later in the same or another computer environment.

   Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your 
   serialization/deserialization algorithm should work. You just need to ensure that a binary tree can 
   be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not 
necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000

Solution:
	I'm serializing it like how trees are presented in leetcode.
	Example:
		1,2,3,null,4,5 means
		a. 1 is the root element of the whole tree
		b. 2 and 3 are the LC and RC of 1
		c. 4 is the RC of 2
		d. 5 is the LC of 3
   */

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec 
{
    public:
	// Encodes a tree to a single string.
	std::string serialize(TreeNode* root) 
	{
	    if(!root)
		return "";

	    std::queue<TreeNode*> q;
	    std::string s;

	    q.push(root);
	    s += std::to_string(root->val);

	    //level order traversal and serialization
	    while(!q.empty())
	    {
		if(q.front()->left)
		{
		    s += ',';
		    s += std::to_string(q.front()->left->val);
		    q.push(q.front()->left);
		}
		else
		    s += ",n";

		if(q.front()->right)
		{
		    s += ',';
		    s += std::to_string(q.front()->right->val);
		    q.push(q.front()->right);
		}
		else
		    s += ",n";
		q.pop();
	    }

	    //remove trailing commas and 'n's
	    for(int i{ 0 }; i < s.size(); ++i)
	    {
		if(!(s[s.size() - i - 1] == 'n' || s[s.size() - i - 1] == ','))
		{
		    s.resize(s.size() - i);
		    break;
		}
	    }
	    return s;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(std::string data) 
	{
	    if(data.empty())
		return nullptr;

	    std::string temp;
	    std::queue<TreeNode*> q;

	    int i{};
	    for( ; i < data.size(); ++i)
	    {
		if(data[i] == ',')
		{
		    break;
		}
		else
		{
		    temp += data[i];
		}
	    }

	    auto root{ new TreeNode{stoi(temp)} };
	    q.push(root);

	    ++i;
	    temp.clear();
	    int ctr{};
	    for(; i < data.size(); ++i)
	    {
		if(data[i] == ',' || i == data.size() - 1)
		{
		    if(i == data.size() - 1)
			temp += data[i];

		    auto node{ new TreeNode{stoi(temp)} };
		    q.push(node);
		    if(!ctr)
		    {
			q.front()->left = node;
			++ctr;
		    }
		    else
		    {
			q.front()->right = node;
			--ctr;
			q.pop();
		    }
		    temp.clear();
		}
		else if(data[i] == 'n')
		{
		    if(!ctr)
			++ctr;
		    else
		    {
			--ctr;
			q.pop();
		    }
		    ++i;
		}
		else
		{
		    temp += data[i];
		}
	    }
	    return root;
	}
};

int main()
{
    TreeNode n1{ 1 };
    TreeNode n2{ 2 };
    TreeNode n3{ 3 };
    TreeNode n4{ 4 };
    TreeNode n5{ 5 };
    TreeNode n6{ 6 };
    TreeNode n7{ 7 };

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    //n2.right = &n5;
    n3.left = &n6;
    n3.right = &n7;

    Codec c;
    auto s{ c.serialize(&n1) };
    std::cout << s << '\n';
    
    auto m{ c.deserialize(s) };
    auto t{ c.serialize(m) };
    std::cout << t << '\n';
}

