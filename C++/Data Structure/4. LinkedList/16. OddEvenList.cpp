#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a singly linked list, group all the nodes with odd indices together followed 
	by the nodes with even indices, and return the reordered list.
	The first node is considered odd, and the second node is even, and so on.
	Note that the relative order inside both the even and odd groups should remain as it was in the input.
	
	You must solve the problem in O(1) extra space complexity and O(n) time complexity.

	Examples:
	---------
	Input: head = [1,2,3,4,5]
	Output: [1,3,5,2,4]

	Input: head = [2,1,3,5,6,4,7]
	Output: [2,3,6,7,1,5,4]
	
	Approach:
	---------
	Keep two pointers - odd = head and even = head->next.
    
	iterate the list and make oddtail->next = oddTail->next->next
						and   eventail->next = evenTail->next->next
	At last make oddtail->next = evenhead

	Reference:
	----------
	https://www.youtube.com/watch?v=qf6qp7GzD5Q&pp=ygUUb2RkIGV2ZW4gbGlua2VkIGxpc3Q%3D
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
	ListNode* oddEvenList(ListNode* head) {
		// if no nodes, or 1 node or 2 node, then no change in structure.
		// return head.
		if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
			return head;

		ListNode* oddHead = head, * oddTail = head;
		ListNode* evenHead = head->next, * evenTail = head->next;

		// we are only checking for even node in while condition. Why?
		// even is after odd. so even will exhaust before odd.
		while (evenTail!=nullptr && evenTail->next!=nullptr) {
			oddTail->next = oddTail->next->next;
			evenTail->next = evenTail->next->next;

			oddTail = oddTail->next;
			evenTail = evenTail->next;
		}

		oddTail->next = evenHead;
		return oddHead;
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

	//Test 1 : 1, 2, 3, 4, 5
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(3);
	head1->next->next->next = new ListNode(4);
	head1->next->next->next->next = new ListNode(5);
	printList(head1);

	ListNode* newHead = obj.oddEvenList(head1);
	printList(newHead);

	//Test 2 : 1 2 3 4
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(2);
	head2->next->next = new ListNode(3);
	head2->next->next->next = new ListNode(4);
	printList(head2);

	newHead = obj.oddEvenList(head2);
	printList(newHead);

	return 0;
}