#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	

	Examples: 
	--------
	
*/

struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class Solution {
private:
	void reverseRecursiveUtil(ListNode* &head, ListNode *&current) {
		if (current->next == nullptr) {
			head = current;
			return;
		}

		reverseRecursiveUtil(head, current->next);
		current->next->next = current;
		current->next = nullptr;
	}
public:
	ListNode* reverseIterative(ListNode* head) {
		if (head == nullptr)
			return head;
		ListNode* current = head, * prev = nullptr, * next = nullptr;
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
		return head;
	}

	ListNode* reverseRecursive(ListNode* head) {
		ListNode* current = head;
		reverseRecursiveUtil(head, current);
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

	//Test 1 : 17->15->8->12->10->5->4->1->7->6->NULL
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(3);
	head1->next->next->next = new ListNode(4);
	head1->next->next->next->next = new ListNode(5);
	printList(head1);

	ListNode* newHead = obj.reverseIterative(head1);
	printList(newHead);
	newHead = obj.reverseRecursive(newHead);
	printList(newHead);


	//Test 2 : 8->12->10->5->4->1->6->NULL
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(2);
	head2->next->next = new ListNode(1);
	head2->next->next->next = new ListNode(2);
	head2->next->next->next->next = new ListNode(1);
	head2->next->next->next->next->next = new ListNode(2);
	printList(head2);

	newHead = obj.reverseIterative(head2);
	printList(newHead);
	newHead = obj.reverseRecursive(newHead);
	printList(newHead);

	return 0;
}