#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given the heads of two sorted linked lists list1 and list2.
	Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
	Return the head of the merged linked list.

	Examples:
	---------
	Input: head1 = [5, 10, 15, 40]
		   head2 = [2, 3, 20] 
	Output: 2 -> 3 -> 5 -> 10 -> 15 -> 20 -> 40

	Input: head1 = [1 ,1]
		   head2 = [2, 4]
	Output: 1 -> 1 -> 2 -> 4
	
	Approach:
	---------
	1. Use Recursion
		The idea is to pick the smaller head node at each step and let recursion merge the remaining parts. 
		If one list is empty, return the other; otherwise the smaller node becomes the next node in the merged 
		list and its next is the recursive merge of the rest.

	2. Iterative using dummyNode
		The idea is to iteratively merge two sorted linked lists using a dummy node to simplify the process. 
		A current pointer tracks the last node of the merged list. We compare the nodes from both lists and 
		append the smaller node to the merged list. Once one list is fully traversed, the remaining nodes 
		from the other list are appended. The merged list is returned starting from the node after the dummy node.
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
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		if (list1 == nullptr)
			return list2;
		if (list2 == nullptr)
			return list1;
		
		ListNode* node = nullptr;
		if (list1->data <= list2->data) {
			list1->next = mergeTwoLists(list1->next, list2);
			return list1;
		}
		else {
			list2->next = mergeTwoLists(list1, list2->next);
			return list2;
		}
	}

	ListNode* mergeTwoListsIterative(ListNode* list1, ListNode* list2) {
		ListNode* dummyNode = new ListNode(0);
		ListNode* current = dummyNode;
		while (list1 != nullptr && list2 != nullptr) {
			if (list1->data <= list2->data) {
				current->next = list1;
				current = current->next;
				list1 = list1->next;
			}
			else {
				current->next = list2;
				current = current->next;
				list2 = list2->next;
			}
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

	//Test 1 : 
	ListNode* head1 = new ListNode(5);
	head1->next = new ListNode(10);
	head1->next->next = new ListNode(15);
	head1->next->next->next = new ListNode(40);

	ListNode *head2 = new ListNode(2);
	head2->next = new ListNode(3);
	head2->next->next = new ListNode(20);

	printList(head1);
	printList(head2);
	
	ListNode* newHead = obj.mergeTwoLists(head1, head2);
	printList(newHead);
	
	//Test 2 : 
	cout << "Test 2" << endl;
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(1);

	ListNode* head4 = new ListNode(2);
	head4->next = new ListNode(4);

	printList(head3);
	printList(head4);
	
	newHead = obj.mergeTwoListsIterative(head3, head4);
	printList(newHead);
	return 0;
}