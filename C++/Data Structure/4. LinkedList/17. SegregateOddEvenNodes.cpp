#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a Linked List of integers, The task is to modify the linked list such that all even numbers appear before all 
	the odd numbers in the modified linked list. Also, preserve the order of even and odd numbers.

	Examples: 
	--------
	Input: 17->15->8->12->10->5->4->1->7->6->NULL
	Output: 8->12->10->4->6->17->15->5->1->7->NULL
	Explanation: In the output list, we have all the even nodes first (in the same order as input list, then all the odd nodes 
	of the list (in the same order as input list).

	Input: 8->12->10->5->4->1->6->NULL
	Output: 8->12->10->4->6->5->1->NULL
	Explanation: We do not change the list as all the numbers are even.
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
	ListNode* segregateOddEvenNodes(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;

		ListNode* current = head;
		ListNode* oddHead = nullptr, * oddTail = nullptr;
		ListNode* evenHead = nullptr, * evenTail = nullptr;

		while (current!=nullptr) {
			//even value
			if (current->data % 2 == 0) {
				if (evenHead == nullptr) {
					evenHead = current;
					evenTail = current;
				}
				else {
					evenTail->next = current;
					evenTail = evenTail->next;
				}
			}
			//odd value
			else {
				if (oddHead == nullptr) {
					oddHead = current;
					oddTail = current;
				}
				else {
					oddTail->next = current;
					oddTail = oddTail->next;
				}
			}
			current = current->next;
		}

		// Terminate the odd list
		oddTail->next = nullptr;

		// Combine even and odd lists
		evenTail->next = oddHead;

		return evenHead;
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
	ListNode* head1 = new ListNode(17);
	head1->next = new ListNode(15);
	head1->next->next = new ListNode(8);
	head1->next->next->next = new ListNode(12);
	head1->next->next->next->next = new ListNode(10);
	head1->next->next->next->next->next = new ListNode(5);
	head1->next->next->next->next->next->next = new ListNode(4);
	head1->next->next->next->next->next->next->next = new ListNode(1);
	head1->next->next->next->next->next->next->next->next = new ListNode(7);
	head1->next->next->next->next->next->next->next->next->next = new ListNode(6);
	printList(head1);

	ListNode* newHead = obj.segregateOddEvenNodes(head1);
	printList(newHead);

	//Test 2 : 8->12->10->5->4->1->6->NULL
	ListNode* head2 = new ListNode(8);
	head2->next = new ListNode(12);
	head2->next->next = new ListNode(10);
	head2->next->next->next = new ListNode(5);
	head2->next->next->next->next = new ListNode(4);
	head2->next->next->next->next->next = new ListNode(1);
	head2->next->next->next->next->next->next = new ListNode(6);
	printList(head2);

	newHead = obj.segregateOddEvenNodes(head2);
	printList(newHead);

	return 0;
}