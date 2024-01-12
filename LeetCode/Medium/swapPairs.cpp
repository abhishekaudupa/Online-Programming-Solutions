#include <iostream>

/*
   Swap Nodes in Pairs

   Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)



   Example 1

   Input- head = [1,2,3,4]
   Output- [2,1,4,3]

   Example 2

   Input- head = []
   Output- []

   Example 3

   Input- head = [1]
   Output- [1]

   Constraints

   The number of nodes in the list is in the range [0, 100].
   0 <= Node.val <= 100

   Solution - O(n).
   Swap two consecutive nodes on entry - head and it's next.
   Recursively swap if a next 'pair' exists else stop.

 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
	ListNode* swapPairs(ListNode *head) {

	    //null head.
	    if(!head)
		return head;

	    //just head.
	    if(!(head->next))
		return head;

	    //swap head with next.
	    ListNode *temp = head->next;
	    head->next = temp->next;
	    temp->next = head;

	    //save the temp (which is at head position right now).
	    ListNode *t2 = temp;

	    //check if next pair exists.
	    if(head->next) {
		if(head->next->next) {

		    //if next pair exists...

		    //set temp as next recursive call's head.
		    temp = head->next;

		    //link head to next pair's second node.
		    head->next = temp->next;

		    //recursive call.
		    swapPairs(temp);
		}
	    }

	    //return the new head of the list.
	    return t2;
	}
};

int main() {
    ListNode n1 = {1, NULL};
    ListNode n2 = {2, NULL};
    ListNode n3 = {3, NULL};
    ListNode n4 = {4, NULL};
    ListNode n5 = {5, NULL};

    //n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;

    ListNode *head = &n1;

    ListNode *trav = head;
    while(trav) {
	std::cout << trav->val << ' ';
	trav = trav->next;
    }
    std::cout << '\n';

    Solution s;

    head = s.swapPairs(head);

    trav = head;
    while(trav) {
	std::cout << trav->val << ' ';
	trav = trav->next;
    }

    std::cout << '\n';
}

