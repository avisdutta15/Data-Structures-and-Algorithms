#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a singly linked list with two values x and y, the task is to swap two nodes having values x and y without swapping data.

	Examples:
	---------
	Input :  1->2->3->4->5, x = 2, y = 4
	output:  1->4->3->2->5 

	Input: 10->15->12->13->20->14,  x = 10, y = 20
	Output: 20->15->12->13->10->14

	Approach:
	-----------
	Possible cases to handle:
	When swapping 2 nodes, x and y, in a linked list, there are a few cases that can arise:

	x and y are adjacent to each other, and
		One of x or y is the head node of the list.
		None of x or y is either a head node or a tail node.
	x and y are not adjacent to each other, and:
		One of x or y is the head node of the list.
		None of x or y is either a head node or a tail node.
	x or y don’t even exist in the linked list.
	
	Therefore, our solution must handle all these cases.


	Follow the steps below to solve the problem:

	1. If x and y are the same, return as no need to swap.
	2. Start traversing the List to search for x and y nodes by keeping track of the previous nodes prevX and prevY.
	3. If either x or y is not found in the list, return without making any changes.
		else, 
	4. update connections (first update prev and then next):
			If x is not the head, set prevX->next to currY. Otherwise, set currY as the new head.
			If y is not the head, set prevY->next to currX. Otherwise, set currX as the new head.
			
			Swap the next pointers of currX and currY to complete the swap.

	Reference:
	----------
	https://www.geeksforgeeks.org/dsa/swap-nodes-in-a-linked-list-without-swapping-data/
*/

class ListNode {
public:
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class Solution {
private:
public:
	ListNode* swapTwoNodes(ListNode* head, int key1, int key2) {
		if (head == nullptr)
			return head;

		//find the nodes
		ListNode* node1 = head, * node2 = head;
		ListNode* prevNode1 = nullptr, * prevNode2 = nullptr;
		while (node1 != nullptr) {
			if (node1->data == key1)
				break;
			prevNode1 = node1;
			node1 = node1->next;
		}

		//if key 1 is not present, then return
		if (node1 == nullptr)
			return head;

		while (node2 != nullptr) {
			if (node2->data == key2)
				break;
			prevNode2 = node2;
			node2 = node2->next;
		}

		//if key 2 is not present, then return
		if (node2 == nullptr)
			return head;

		//first fix the prev pointers.
		if (prevNode1 != nullptr) {
			prevNode1->next = node2;
		}
		else {
			//node 1 is the head. so make node2 as head
			head = node2;
		}

		if (prevNode2 != nullptr) {
			prevNode2->next = node1;
		}
		else {
			//node 2 is the head. so make node1 as head
			head = node1;
		}

		//now fix the next pointers.
		ListNode* temp = node1->next;
		node1->next = node2->next;
		node2->next = temp;

		return head;
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

int main() {
	Solution obj;

	//Test 1 :	5->10->2->3
	ListNode* head1 = new ListNode(5);
	head1->next = new ListNode(10);
	head1->next->next = new ListNode(2);
	head1->next->next->next = new ListNode(3);
	head1->next->next->next->next = new ListNode(4);

	printList(head1);

	ListNode* newHead = obj.swapTwoNodes(head1, 10, 3);
	printList(newHead);

	newHead = obj.swapTwoNodes(newHead, 5, 4);
	printList(newHead);

	return 0;
}