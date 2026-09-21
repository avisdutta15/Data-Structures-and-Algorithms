#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an unsorted linked list containing n nodes, the task is to remove duplicate nodes while preserving the original order.

	Examples:
	--------
	Input: 12 -> 11 -> 12 -> 21 -> 41 -> 43 -> 21
	Output: 12 -> 11 -> 21 -> 41 -> 43
	Explanation: The second occurrence of 12 (the one after 11) and the second occurrence of 21 (the one at the end) are removed,
	resulting in a linked list that maintains the order of their first appearances.

	Input: 1 -> 2 -> 3 -> 2 -> 4
	Output: 1 -> 2 -> 3 -> 4
	Explanation: Similarly, the second occurrence of 2 is removed, ensuring that each number appears only once while maintaining
	the order of their first appearances.

	Approach:
	--------
	HashSet
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

		unordered_set<int> hashSet;
		ListNode* current = head, *prevNode = nullptr;
		ListNode* nodeToDelete = nullptr;
		while (current != nullptr) {
			if (hashSet.find(current->data) == hashSet.end()) {
				hashSet.insert(current->data);
				prevNode = current;
				current = current->next;
			}
			else {
				nodeToDelete = current;
				prevNode->next = current->next;
				current = current->next;
				delete(nodeToDelete);
				nodeToDelete = nullptr;
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
	ListNode* head1 = new ListNode(12);
	head1->next = new ListNode(11);
	head1->next->next = new ListNode(12);
	head1->next->next->next = new ListNode(21);
	head1->next->next->next->next = new ListNode(41);
	head1->next->next->next->next->next = new ListNode(43);
	head1->next->next->next->next->next->next = new ListNode(21);
	printList(head1);

	ListNode* newHead = obj.deleteDuplicates(head1);
	printList(newHead);

	//Test 2
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(2);
	head2->next->next = new ListNode(3);
	head2->next->next->next = new ListNode(2);
	head2->next->next->next->next = new ListNode(4);
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