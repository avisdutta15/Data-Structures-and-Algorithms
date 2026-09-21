#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a singly linked list, we need to sort the linked list in non-decreasing order using merge sort.

	Examples:
	---------
	Input: 9 -> 8 -> 5 -> 2
	O/P:   2 -> 5 -> 8 -> 9

	Approach:
	---------
	Here we have to maintain a MergeSort function that sorts the list in three steps:

	Split the List into Two Halves: 
			Use two pointers, fast and slow, starting at the head. 
			Move fast two steps and slow one step. When fast reaches the end, slow is at the midpoint. 
			Split the list into two halves: the first half from head to just before slow, and the second from slow->next to the end. 
			Set slow->next to NULL.
	Apply MergeSort Recursively: 
			Recursively call MergeSort() on both halves. 
			The base case is when the list is empty (head == NULL) or has one node (head->next == NULL), in which case return the list as is.
	Merge the Two Sorted Halves: 
			After sorting both halves, call merge() to merge them by comparing nodes and linking accordingly. 
			Append any remaining nodes from the exhausted half. 
			Finally, returns the new head of the sorted list.
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
	// Why do we have return slow prev in case of even number of nodes?
	// Because in case of even number of nodes, we have 2 middle nodes. We should return the second last
	// middle node to avoid StackOverflow Exception.
	// Suppose we have list {1, 2}
	// We call findMiddleNode(list)
	// We should get 1 as the middle node. If we do not have that condition, we would get 2 as middlenode.
	// If we get 2 as middle node, then leftList {1, 2} and rightList {nullptr}
	// And we would again call the sort on leftList {1, 2} and rightList {nullptr}. 
	// This would cause StackOverflow Exception as leftList is always equals the original list.
	// To fix this in case of even number of nodes e.g. - {1, 2} we have 2 middle nodes.
	// We should return the second last middle node {1}. Then calling sort on leftList {1} and rightList{2}
	// would not give StackOverflow
	ListNode* findMiddleNode(ListNode* head) {
		ListNode* fast = head, * slow = head, * slowPrev = nullptr;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slowPrev = slow;
			slow = slow->next;
		}
		//in case of even number of nodes, get the second last as middle node.
		if (fast == nullptr)
			return slowPrev;

		return slow;
	}

	ListNode* mergeLists(ListNode* list1, ListNode* list2) {
		if (list1 == nullptr)
			return list2;
		if (list2 == nullptr)
			return list1;
		if (list1 == nullptr && list2 == nullptr)
			return nullptr;

		ListNode* dummyNode = new ListNode(0);
		ListNode* current = dummyNode;
		while (list1 != nullptr && list2 != nullptr) {
			if (list1->data <= list2->data) {
				current->next = list1;
				list1 = list1->next;
			}
			else {
				current->next = list2;
				list2 = list2->next;
			}
			current = current->next;
		}

		while (list1 != nullptr) {
			current->next = list1;
			current = current->next;
			list1 = list1->next;
		}

		while (list2 != nullptr) {
			current->next = list2;
			current = current->next;
			list2 = list2->next;
		}

		return dummyNode->next;
	}

public:
	ListNode* mergeSort(ListNode* head) {
		//base case: single node then return
		if (head == nullptr || head->next == nullptr)
			return head;

		//find the middle node
		ListNode* middleNode = findMiddleNode(head);

		//Segregate the lists
		ListNode* leftList = nullptr, * rightList = nullptr;
		leftList = head;
		rightList = middleNode->next;
		middleNode->next = nullptr;

		//Recursively sort each half
		leftList = mergeSort(leftList);
		rightList = mergeSort(rightList);

		//Merge the two halves
		return mergeLists(leftList, rightList);
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

	//Test 1 :	9 -> 8 -> 5 -> 2
	//	  O/P:	2 -> 5 -> 8 -> 9
	ListNode* head1 = new ListNode(9);
	head1->next = new ListNode(8);
	head1->next->next = new ListNode(5);
	head1->next->next->next = new ListNode(2);
	
	printList(head1);

	ListNode* newHead = obj.mergeSort(head1);
	printList(newHead);

	//Test 2 :	9 -> 8 -> 5 -> 2 -> 1
	//	  O/P:	1 -> 2 -> 5 -> 8 -> 9
	ListNode* head2 = new ListNode(9);
	head2->next = new ListNode(8);
	head2->next->next = new ListNode(5);
	head2->next->next->next = new ListNode(2);
	head2->next->next->next->next = new ListNode(1);
	printList(head2);

	newHead = obj.mergeSort(head2);
	printList(newHead);

	return 0;
}