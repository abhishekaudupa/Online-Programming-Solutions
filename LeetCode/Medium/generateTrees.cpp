#include <iostream>
#include <vector>

/*
   Unique Binary Search Trees II

   Given an integer n, return all the structurally unique BST's 
   (binary search trees), which has exactly n nodes of unique values 
   from 1 to n. Return the answer in any order.

   Example 1:

   Input- n = 3
   Output- [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]

   Example 2:

   Input- n = 1
   Output- [[1]]

   Constraints-

   1 <= n <= 8

   Solution
   The idea is to start with a list with 1 tree with 1 node (node with value 1). 
   Now we take a node with value 2 and make it as the root of the previous tree 
   (with just 1 node). Next, we take another node with value 2 and insert it at 
   the end of the previous tree(with just 1 node). The list now has 2 unique BSTs.

   Similarly, we insert node with value 3 as the root, as a leaf and in the
   interstitial spots in the previous trees. This gives us 5 unique BSTs.

   As we continue to do this, the list of unique BSTs with unique elements grows
   towards the required answer.

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

void print_tree(TreeNode *root) {
    //preorder 
    if(root) {
	std::cout << root->val << ' ';
    } else {
	std::cout << "NULL ";
	return;
    }

    print_tree(root->left);
    print_tree(root->right);
}

class Solution {
    std::vector<TreeNode*> v;

    public:
    inline TreeNode *get_new_node(int ele, TreeNode *left = NULL, TreeNode *right = NULL) {

	//our unique tree list.
	return new TreeNode(ele, left, right);
    }

    inline void append_to_tree(TreeNode *root, TreeNode *node) {
	//we're inserting biggest element.

	//traverser.
	TreeNode *trav = root;

	//traverse to rightmost node.
	while(trav->right)
	    trav = trav->right;

	//insert node to right of the rightmost node.
	trav->right = node;
    }

    inline TreeNode *duplicate_tree(TreeNode *root) {

	if(root) {
	    //duplicate the root.
	    auto new_root = get_new_node(root->val);

	    //duplicate left sub-tree.
	    new_root->left = duplicate_tree(root->left);

	    //duplicate right sub-tree.
	    new_root->right = duplicate_tree(root->right);

	    //return the duplicated tree.
	    return new_root;
	}
	return NULL;
    }

    inline TreeNode *duplicate_tree_with_insertion(TreeNode *root, int after, int ele) {
	if(root) {
	    //duplicate the root.
	    auto new_root = get_new_node(root->val);

	    //if we have to insert new element after root...
	    if(new_root->val == after) {

		//insert new element (biggest) to the right of the new root.
		new_root->right = get_new_node(ele);

		//duplicate the right su-btree to its left, without anymore insertions.
		new_root->right->left = duplicate_tree(root->right);

		//duplicate the left sub-tree, without anymore insertions.
		new_root->left = duplicate_tree(root->left);

		//return the duplicated tree.
		return new_root;
	    }

	    //otherwise.

	    //duplicate the left sub-tree.
	    new_root->left = duplicate_tree_with_insertion(root->left, after, ele);

	    //duplicate the right sub-tree.
	    new_root->right = duplicate_tree_with_insertion(root->right, after, ele);

	    //return duplicated tree.
	    return new_root;
	}
	return NULL;
    }

    inline void insert_in_tree(int ele) {

	//get the current size of our tree list.
	auto vs = v.size();

	//for each tree in the list.
	for(int i = 0; i < vs; ++i) {

	    //make element as the root.
	    auto temp = get_new_node(ele);
	    temp->left = duplicate_tree(v[i]);
	    v.push_back(temp);

	    //insert element in between.
	    temp = v[i];
	    while(temp) {

		if(temp->right) {
		    auto duplicate = duplicate_tree_with_insertion(v[i], temp->val, ele);
		    v.push_back(duplicate);
		}
		temp = temp->right;
	    }

	    //insert element at last.
	    append_to_tree(v[i], get_new_node(ele));

	}
    }

    std::vector<TreeNode*> generateTrees(int n) {

	//base case: List with one tree with one node.
	if(n == 1) {
	    v.push_back(get_new_node(1));
	    return v;
	}

	//recursive case.

	//call recursive.
	generateTrees(n - 1);

	//grow the list.
	insert_in_tree(n);

	//return the list.
	return v;
    }
};

int main() {
    std::cout << "Enter n: ";
    int n;
    std::cin >> n;

    Solution s;
    int i = 1;
    auto set = s.generateTrees(n);
    for(auto& ele: set) {
	std::cout << i++ << ". ";
	print_tree(ele);
	std::cout << '\n';
    }
}
