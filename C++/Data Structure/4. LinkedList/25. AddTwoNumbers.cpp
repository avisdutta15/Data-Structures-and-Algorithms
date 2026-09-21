#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given two non-empty linked lists representing two non-negative integers. 
	The digits are stored in reverse order, and each of their nodes contains a single digit. 
	Add the two numbers and return the sum as a linked list.

	You may assume the two numbers do not contain any leading zero, except the number 0 itself.

	Example:
	Input: l1 = [2,4,3], l2 = [5,6,4]
	Output: [7,0,8]
	Explanation: 342 + 465 = 807.

	Input: l1 = [0], l2 = [0]
	Output: [0]

	Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
	Output: [8,9,9,9,0,0,0,1]


	Approach:
	---------
	
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
	ListNode* tail = nullptr;
	void push_back(ListNode*& head, int data) {
		ListNode* node = new ListNode(data);
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr;
		
		int sum = 0;
		int carry = 0;
		while (l1 != nullptr && l2 != nullptr) {
			carry = carry > 0 ? carry : 0;
			sum = l1->data + l2->data + carry;
			if (sum > 9) {
				sum = sum % 10;
				carry = 1; //coz max value of carry can be 1 [9+9 = 18. carry 1]
			}
			else {
				carry = 0;
			}

			push_back(head, sum);	
			l1 = l1->next;
			l2 = l2->next;
		}

		while (l1 != nullptr) {
			carry = carry > 0 ? carry : 0;
			sum = l1->data + carry;
			carry = 0;
			if (sum > 9) {
				sum = sum % 10;
				carry = 1; //coz max value of carry can be 1 [9+9 = 18. carry 1]
			}

			push_back(head, sum);
			l1 = l1->next;
		}
		while (l2 != nullptr) {
			carry = carry > 0 ? carry : 0;
			sum = l2->data + carry;
			carry = 0;
			if (sum > 9) {
				sum = sum % 10;
				carry = 1; //coz max value of carry can be 1 [9+9 = 18. carry 1]
			}

			push_back(head, sum);
			l2 = l2->next;
		}

		//we can have a carry. add this to the list
		if (carry != 0)
			push_back(head, carry);

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

	//Test 1 : 1->2->3->4->5->6->NULL
	ListNode* head1 = new ListNode(2);
	head1->next = new ListNode(4);
	head1->next->next = new ListNode(3);

	ListNode* head2 = new ListNode(5);
	head2->next = new ListNode(6);
	head2->next->next = new ListNode(4);

	printList(head1);
	printList(head2);


	ListNode* newHead = obj.addTwoNumbers(head1, head2);
	printList(newHead);
	

	//Test 2 : 8->12->10->5->4->1->6->NULL
	ListNode* head3 = new ListNode(9);
	head3->next = new ListNode(9);
	head3->next->next = new ListNode(9);
	head3->next->next->next = new ListNode(9);
	head3->next->next->next->next = new ListNode(9);
	head3->next->next->next->next->next = new ListNode(9);
	head3->next->next->next->next->next->next = new ListNode(9);

	ListNode* head4 = new ListNode(9);
	head4->next = new ListNode(9);
	head4->next->next = new ListNode(9);
	head4->next->next->next = new ListNode(9);
	printList(head3);
	printList(head4);

	newHead = obj.addTwoNumbers(head3, head4);
	printList(newHead);
	
	return 0;
}