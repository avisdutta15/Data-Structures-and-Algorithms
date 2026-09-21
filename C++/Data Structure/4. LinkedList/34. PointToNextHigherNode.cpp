#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a singly linked list with every node having an additional arbitrary pointer that currently points to NULL. 
	The task is to make the arbitrary pointer point to the next higher-value node.


	Examples:
	---------
	Input :  [data: 5, arbit: null, next:]-> [data:10, arbit:null, next: ]-> [data:2, arbit:null, next:] -> [data:3, arbit:null, next:null]
	output:  [data: 5, arbit: 10, next:]-> [data:10, arbit:null, next: ]-> [data:2, arbit:3, next:] -> [data:3, arbit:3, next:null]

	Approach:
	-----------
	Using Merge Sort - O(nlogn) Time and O(n) Space
	The approach involves using a modified Merge Sort for linked list while maintaining the original 
	sequence and linking each node to the next higher value using an auxiliary arbit pointer. 
	Initially, the arbit pointer of each node is set to point to the next node. The list is recursively 
	split into smaller sections, which are then sorted and merged back together. During merging, 
	the arbit pointers are updated to point to the next higher value node. This method efficiently 
	sorts the list and adjusts the arbit pointers to maintain the desired order without altering 
	the original list structure.

	Reference:
	----------
	https://www.geeksforgeeks.org/dsa/point-to-next-higher-value-node-in-a-linked-list-with-an-arbitrary-pointer/
*/

class ListNode {
public:
	int data;
	ListNode* next;
	ListNode* arbit;
	ListNode() : data(0), next(nullptr), arbit(nullptr) {}
	ListNode(int data) : data(data), next(nullptr), arbit(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next), arbit(nullptr) {}
};

class Solution {
private:
	ListNode* findMiddleNode(ListNode* head) {
		ListNode* fast = head, * slow = head, * slowPrev = nullptr;
		while (fast != nullptr && fast->arbit != nullptr) {
			fast = fast->arbit->arbit;
			slowPrev = slow;
			slow = slow->arbit;
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
				current->arbit = list1;
				list1 = list1->arbit;
			}
			else {
				current->arbit = list2;
				list2 = list2->arbit;
			}
			current = current->arbit;
		}

		while (list1 != nullptr) {
			current->arbit = list1;
			current = current->arbit;
			list1 = list1->arbit;
		}

		while (list2 != nullptr) {
			current->arbit = list2;
			current = current->arbit;
			list2 = list2->arbit;
		}

		return dummyNode->arbit;
	}

	ListNode* mergeSort(ListNode* head) {
		//base case: single node then return
		if (head == nullptr || head->arbit == nullptr)
			return head;

		//find the middle node
		ListNode* middleNode = findMiddleNode(head);

		//Segregate the lists
		ListNode* leftList = nullptr, * rightList = nullptr;
		leftList = head;
		rightList = middleNode->arbit;
		middleNode->arbit = nullptr;

		//Recursively sort each half
		leftList = mergeSort(leftList);
		rightList = mergeSort(rightList);

		//Merge the two halves
		return mergeLists(leftList, rightList);
	}

public:
	ListNode* pointNextGreaterElement(ListNode* head) {
		if (head == nullptr)
			return head;

		ListNode* current = head;
		while (current != nullptr) {
			current->arbit = current->next;
			current = current->next;
		}

		return mergeSort(head);
	}
};

void printListArbit(ListNode* node) {
	if (node == nullptr) {
		cout << "List is empty." << endl;
		return;
	}
	while (node != nullptr) {
		cout << node->data << " ";
		node = node->arbit;
	}
	cout << endl;
}

void printListNext(ListNode* node) {
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

	printListNext(head1);

	ListNode* newHead = obj.pointNextGreaterElement(head1);
	printListNext(head1);
	printListArbit(newHead);

	return 0;
}