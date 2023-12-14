#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>

/*
   Clone Graph

   Given a reference of a node in a connected undirected graph.

   Return a deep copy (clone) of the graph.

   Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

   Test case format:

   For simplicity, each node's value is the same as the node's index (1-indexed). For example, the first node with val == 1, the second node with val == 2, and so on. The graph is represented in the test case using an adjacency list.

   An adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

   The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.

   Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3:
Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.


Constraints:

The number of nodes in the graph is in the range [0, 100].
1 <= Node.val <= 100
Node.val is unique for each node.
There are no repeated edges and no self-loops in the graph.
The Graph is connected and all nodes can be visited starting from the given node.

Solution:
	We traverse the graph (BFS). While traversing, we create adjacent node copies and link 'em to the
	one we're currently visiting.

	See code for detailed comments.
 */

// Definition for a Node.
class Node {
    public:
	int val;
	std::vector<Node*> neighbors;

	Node() {
	    val = 0;
	    neighbors = std::vector<Node*>();
	}

	Node(int _val) {
	    val = _val;
	    neighbors = std::vector<Node*>();
	}

	Node(int _val, std::vector<Node*> _neighbors) {
	    val = _val;
	    neighbors = _neighbors;
	}
};

class Solution {
    using node_pair_t = std::pair<Node*, Node*>;
    public:
    Node* cloneGraph(Node* node) {
	//null node check.
	if(!node)
	    return nullptr;

	//get a queue to do BFS
	std::queue<node_pair_t> search_queue;

	//get a unordered map to keep track of to-visit nodes and created copies.
	std::unordered_map<Node*, Node*> to_visit;

	//create a copy of the input node.
	auto genesis_node = new Node(node->val);

	//get a node pair object.
	auto genesis_node_pair = std::make_pair(node, genesis_node);

	//insert original and the copy to the map.
	to_visit.insert(genesis_node_pair);

	//insert the node pair to the queue for BFS.
	search_queue.push(genesis_node_pair);

	//start BFS
	while(!search_queue.empty()) {

	    //get the search nodes.
	    auto original_node = search_queue.front().first;
	    auto copy_node = search_queue.front().second;

	    //explore all neighbors of the current search node.
	    for(const auto& neighbor: original_node->neighbors) {

		//search if the neighbor is in the to-visit map.
		auto scheduled_for_visit = to_visit.find(neighbor);

		//check if the neighbor is not scheduled for a visit.
		if(scheduled_for_visit == to_visit.end()) {

		    /* if a neighbor is not scheduled for a visit yet, it's
		       copy/clone isn't created yet either */

		    //create a copy of it.
		    auto neighbor_copy = new Node(neighbor->val);

		    //link it to the copy node.
		    copy_node->neighbors.push_back(neighbor_copy);

		    //get a node pair object
		    auto neightbor_node_pair = std::make_pair(neighbor, neighbor_copy);

		    //insert the pair to search queue.
		    search_queue.push(neightbor_node_pair);

		    //insert the pair to the map.
		    to_visit.insert(neightbor_node_pair);
		} else {

		    /* if a neighbor is already scheduled for a visit, then it's clone
		       already exists and the copy_node has to be linked to it */
		    copy_node->neighbors.push_back(scheduled_for_visit->second);
		}
	    }

	    //pop the queue.
	    search_queue.pop();
	}

	std::cout << '\n';
	return genesis_node;
    }

    //graph traverser with detail output. For checking above function.
    void print_graph_details(Node *node) {
	if(!node)
	    return;

	std::queue<Node*> search_q;
	std::unordered_set<int> to_visit;

	to_visit.insert(node->val);
	search_q.push(node);

	while(!search_q.empty()) {
	    auto cur_node = search_q.front();

	    std::cout << "Curr. node is " << cur_node->val << '(' << cur_node << "). Neighbors are ";

	    for(const auto& ele: cur_node->neighbors) {
		std::cout << ele->val << ' ';
		if(to_visit.find(ele->val) == to_visit.end()) {
		    to_visit.insert(ele->val);
		    search_q.push(ele);
		}
	    }
	    std::cout << '\n';

	    search_q.pop();
	}
    }
};

int main()
{
    Solution s;

    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);
    Node *n5 = new Node(5);

    n1->neighbors.push_back(n2);
    n1->neighbors.push_back(n4);
    n1->neighbors.push_back(n5);

    n2->neighbors.push_back(n3);
    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n4);

    n3->neighbors.push_back(n2);
    n3->neighbors.push_back(n4);
    n3->neighbors.push_back(n5);

    n4->neighbors.push_back(n1);
    n4->neighbors.push_back(n3);
    n4->neighbors.push_back(n2);

    n5->neighbors.push_back(n3);
    n5->neighbors.push_back(n1);

    s.print_graph_details(n1);
    auto clone = s.cloneGraph(n1);
    s.print_graph_details(clone);
}

