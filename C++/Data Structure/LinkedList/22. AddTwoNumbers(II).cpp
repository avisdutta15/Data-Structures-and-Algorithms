#include <iostream>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given two non-empty linked lists representing two non-negative integers. 
	The most significant digit comes first and each of their nodes contains a single digit. 
	Add the two numbers and return the sum as a linked list.

	You may assume the two numbers do not contain any leading zero, except the number 0 itself.

	Examples:
	---------
	Input: l1 = [7,2,4,3], l2 = [5,6,4]
	Output: [7,8,0,7]
	7	->	2	->	4	->	3
			5	->	6	->	4
	-------------------------
	7	->	8	->	0	->	7


	Example 2:
	Input: l1 = [2,4,3], l2 = [5,6,4]
	Output: [8,0,7]
	
	Example 3:
	Input: l1 = [0], l2 = [0]
	Output: [0]

	Follow up: Could you solve it without reversing the input lists?

	Approach:
	---------
	Recursion can be tough. We can simulate recursion by using stack.
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
	void push_front(ListNode*& head, int data) {
		ListNode* node = new ListNode(data);
		if (head == nullptr) {
			head = node;
		}
		else {
			node->next = head;
			head = node;
		}
	}
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr;
		
		stack<int> stack1;
		stack<int> stack2;

		while (l1 != nullptr) {
			stack1.push(l1->data);
			l1 = l1->next;
		}

		while (l2 != nullptr) {
			stack2.push(l2->data);
			l2 = l2->next;
		}

		int sum = 0;
		int carry = 0;
		while (stack1.size() != 0 && stack2.size() != 0) {
			carry = carry > 0 ? carry : 0;
			sum = stack1.top() + stack2.top() + carry;
			if (sum > 9) {
				sum = sum % 10;
				carry = 1; //coz max value of carry can be 1 [9+9 = 18. carry 1]
			}
			else {
				carry = 0;
			}

			push_front(head, sum);
			stack1.pop();
			stack2.pop();
		}

		while (stack1.size() != 0) {
			carry = carry > 0 ? carry : 0;
			sum = stack1.top() + carry;
			carry = 0;
			if (sum > 9) {
				sum = sum % 10;
				carry = 1; //coz max value of carry can be 1 [9+9 = 18. carry 1]
			}

			push_front(head, sum);
			stack1.pop();
		}
		while (stack2.size() != 0) {
			carry = carry > 0 ? carry : 0;
			sum = stack2.top() + carry;
			carry = 0;
			if (sum > 9) {
				sum = sum % 10;
				carry = 1; //coz max value of carry can be 1 [9+9 = 18. carry 1]
			}

			push_front(head, sum);
			stack2.pop();
		}

		//we can have a carry. add this to the list
		if (carry != 0)
			push_front(head, carry);

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
	ListNode* head1 = new ListNode(7);
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(4);
	head1->next->next->next = new ListNode(3);

	ListNode* head2 = new ListNode(5);
	head2->next = new ListNode(6);
	head2->next->next = new ListNode(4);

	printList(head1);
	printList(head2);


	ListNode* newHead = obj.addTwoNumbers(head1, head2);
	printList(newHead);
	

	//Test 2 : 8->12->10->5->4->1->6->NULL
	ListNode* head3 = new ListNode(2);
	head3->next = new ListNode(4);
	head3->next->next = new ListNode(3);

	ListNode* head4 = new ListNode(5);
	head4->next = new ListNode(6);
	head4->next->next = new ListNode(4);
	printList(head3);
	printList(head4);

	newHead = obj.addTwoNumbers(head3, head4);
	printList(newHead);
	
	return 0;
}