#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	A linked list of length n is given such that each node contains an additional random pointer, 
	which could point to any node in the list, or null.

	Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, 
	where each new node has its value set to the value of its corresponding original node. Both 
	the next and random pointer of the new nodes should point to new nodes in the copied list such 
	that the pointers in the original list and copied list represent the same list state. None of 
	the pointers in the new list should point to nodes in the original list.

	For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for 
	the corresponding two nodes x and y in the copied list, x.random --> y.

	Return the head of the copied linked list.

	The linked list is represented in the input/output as a list of n nodes. Each node is represented 
	as a pair of [val, random_index] where:

	val: an integer representing Node.val
	random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or 
	null if it does not point to any node.
	Your code will only be given the head of the original linked list.

	Examples:
	---------
	Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
	Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

	Input: head = [[1,1],[2,1]]
	Output: [[1,1],[2,1]]

	Input: head = [[3,null],[3,0],[3,null]]
	Output: [[3,null],[3,0],[3,null]]
	
	Approach:
	---------
	1. Use Hash Map: TC: O(n) SC: O(n)
		Keep a Hash Map of <oldNode, newNode>
		2 pass.
		Iterate the list and create a new linked list. Popuplate the oldNode and newNode map.
		Iterate the lists and populate the random pointers from the map.
			Special case - do this only if currentnode->random!=nullptr
	3. Insert the new nodes in between the original nodes. TC: O(n) SC: O(1)
		Then fix the random nodes.
		Iterate the lists again an restore the correct next pointers.
		
*/

class ListNode {
public:
	int data;
	ListNode* next;
	ListNode* random = nullptr;
	ListNode() : data(0), next(nullptr), random(nullptr) {}
	ListNode(int data) : data(data), next(nullptr), random(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next), random(nullptr) {}
};

class Solution {
public:
	ListNode* copyRandomList(ListNode* head) {
		unordered_map<ListNode*, ListNode*> oldNewMapping;

		ListNode* newHead = nullptr;
		ListNode* newTail = nullptr;
		ListNode* current = head;
		while (current != nullptr) {
			ListNode *newNode = new ListNode(current->data);
			if (newHead == nullptr) {
				newHead = newNode;
				newTail = newHead;
			}
			else {
				newTail->next = newNode;
				newTail = newTail->next;
			}
			oldNewMapping[current] = newNode;
			current = current->next;
		}

		current = head;
		while (current != nullptr) {
			if (current->random != nullptr) {
				oldNewMapping[current]->random = oldNewMapping[current->random];
			}
			current = current->next;
		}
		return newHead;
	}

	ListNode* copyRandomListOptimized(ListNode* head) {
		if (head == nullptr)
			return head;
		ListNode* newHead = nullptr;
		ListNode* current = head;

		// Link the next pointers
		while (current != nullptr) {
			ListNode* newNode = new ListNode(current->data);
			newNode->next = current->next;
			current->next = newNode;
			current = current->next->next;
		}

		// Link the random pointers
		ListNode* original = head;
		ListNode* copied = head->next;
		while (original->next != nullptr && copied->next!=nullptr) {
			if(original->random!=nullptr)
				copied->random = original->random->next;
			original = original->next->next;
			copied = copied->next->next;
		}

		// For the last node
		if (original->random != nullptr)
			copied->random = original->random->next;

		// Restore the list (relinking the correct next ptrs)
		original = head;
		copied   = head->next;
		newHead = copied;
		while (original->next != nullptr && copied->next!=nullptr) {
			original->next = original->next->next;
			copied->next = copied->next->next;
			original = original->next;
			copied = copied->next;
		}
		// For the last node
		original->next = nullptr;
		copied->next = nullptr;

		return newHead;
	}
};
void printList(ListNode* node) {
	if (node == nullptr) {
		cout << "List is empty." << endl;
		return;
	}
	while (node != nullptr) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

void printRandom(ListNode* node) {
	if (node == nullptr) {
		cout << "List is empty." << endl;
		return;
	}
	while (node != nullptr) {
		if(node->random!=nullptr)
			cout << node->data<< " " << node->random->data << " , ";
		node = node->next;
	}
	cout << endl;
}

int main() {
	Solution obj;

	//Test 1 : 
	ListNode* head1 = new ListNode(7);
	head1->next = new ListNode(13);
	head1->next->next = new ListNode(11);
	head1->next->next->next = new ListNode(10);
	head1->next->next->next->next = new ListNode(1);

	head1->random = nullptr;
	head1->next->random = head1;
	head1->next->next->random = head1->next->next->next->next;
	head1->next->next->next->random = head1->next->next;
	head1->next->next->next->next->random = head1;

	printList(head1);
	printRandom(head1);

	ListNode* newHead = obj.copyRandomList(head1);
	printList(newHead);
	printRandom(newHead);

	//Test 2 : 
	cout << "Test 2" << endl;
	ListNode* head2 = new ListNode(7);
	head2->next = new ListNode(13);
	head2->next->next = new ListNode(11);
	head2->next->next->next = new ListNode(10);
	head2->next->next->next->next = new ListNode(1);

	head2->random = nullptr;
	head2->next->random = head2;
	head2->next->next->random = head2->next->next->next->next;
	head2->next->next->next->random = head2->next->next;
	head2->next->next->next->next->random = head2;

	printList(head2);
	printRandom(head2);

	newHead = obj.copyRandomListOptimized(head2);
	printList(newHead);
	printRandom(newHead);
	return 0;
}