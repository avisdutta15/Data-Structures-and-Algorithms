#include <iostream>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

	Examples:
	--------
	Input: 1 -> 1 -> 2 -> NULL
	Output: 1 -> 2 -> NULL

	Input: 1 -> 1 -> 2 -> 3 -> 3 -> NULL
	Output: 1 -> 2 -> 3 -> NULL

	Approach:
	Delete the next node if the next node is a duplicate.
*/
struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr)
			return head;
		ListNode* current = head;
		ListNode* nodeToBeDeleted = nullptr;
		while (current->next!=nullptr) {
			if (current->data == current->next->data) {
				nodeToBeDeleted = current->next;
				current->next = current->next->next;
				delete(nodeToBeDeleted);
				nodeToBeDeleted = nullptr;
			}
			else {
				current = current->next;
			}			
		}
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

	//Test 1
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(1);
	head1->next->next = new ListNode(2);
	printList(head1);

	ListNode* newHead = obj.deleteDuplicates(head1);
	printList(newHead);

	//Test 2
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(1);
	head2->next->next = new ListNode(2);
	head2->next->next->next = new ListNode(3);
	head2->next->next->next->next = new ListNode(3);
	printList(head2);

	newHead = obj.deleteDuplicates(head2);
	printList(newHead);

	//Test 3
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(1);
	head3->next->next = new ListNode(2);
	head3->next->next->next = new ListNode(2);
	printList(head3);

	newHead = obj.deleteDuplicates(head3);
	printList(newHead);
	
	//Test 4
	ListNode* head4 = new ListNode(1);
	head4->next = new ListNode(1);
	head4->next->next = new ListNode(1);
	head4->next->next->next = new ListNode(1);
	printList(head4);

	newHead = obj.deleteDuplicates(head4);
	printList(newHead);
	return 0;
}