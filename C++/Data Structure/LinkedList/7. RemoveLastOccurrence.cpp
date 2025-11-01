#include <iostream>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a singly linked list and a key, the task is to delete the last occurrence of that key in the linked list.

	Examples:
	--------
	Input: head: 1 -> 2 -> 3 -> 1 -> 4 -> NULL, key = 1
	Output: 1 -> 2 -> 3 -> 4 -> NULL

	Input: head: 1 -> 2 -> 3 -> 4 -> 5 -> NULL , key = 3
	Output: 1 -> 2 -> 4 -> 5 -> NULL

	Approach:
	keep a keynode and keynode prev.
	iterate the list and update them accordingly.
	edge case - keynode not present - return head.
				keynode = head		- update head delete keynode
	delete keynode and return head
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
	ListNode* removeLastOccurence(ListNode* head, int key) {
		if (head == nullptr)
			return nullptr;

		ListNode* currentNode = head, * prevNode = nullptr;
		ListNode* keyNode = nullptr, * keyNodePrev = nullptr;
		while (currentNode != nullptr) {
			if (currentNode->data == key) {
				keyNode = currentNode;
				keyNodePrev = prevNode;
			}
			prevNode = currentNode;
			currentNode = currentNode->next;
		}
		//if key not present then nothing to delete
		if (keyNode == nullptr)
			return head;
		else {
			//if the last occurrence of key = head then update head.
			if (keyNode == head) {
				head = head->next;
			}
			//else delink the keyNode from list
			else {
				keyNodePrev->next = keyNode->next;
			}
			delete(keyNode);
			keyNode = nullptr;
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
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(3);
	head1->next->next->next = new ListNode(4);
	head1->next->next->next->next = new ListNode(1);
	head1->next->next->next->next->next = new ListNode(4);
	printList(head1);

	cout << "Deleting last occurence of 1" << endl;
	ListNode* newHead = obj.removeLastOccurence(head1, 1);
	printList(newHead);

	//Test 2
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(2);
	head2->next->next = new ListNode(3);
	head2->next->next->next = new ListNode(4);
	head2->next->next->next->next = new ListNode(1);
	head2->next->next->next->next->next = new ListNode(4);
	printList(head2);

	cout << "Deleting last occurence of 4" << endl;
	newHead = obj.removeLastOccurence(head2, 4);
	printList(newHead);

	//Test 3
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(2);
	head3->next->next = new ListNode(3);
	head3->next->next->next = new ListNode(4);
	printList(head3);

	cout << "Deleting last occurence of 1" << endl;
	newHead = obj.removeLastOccurence(head3, 1);
	printList(newHead);
	
	//Test 4
	ListNode* head4 = new ListNode(1);
	head4->next = new ListNode(2);
	head4->next->next = new ListNode(3);
	head4->next->next->next = new ListNode(4);
	printList(head4);

	cout << "Deleting last occurence of 5" << endl;
	newHead = obj.removeLastOccurence(head4, 5);
	printList(newHead);
	return 0;
}