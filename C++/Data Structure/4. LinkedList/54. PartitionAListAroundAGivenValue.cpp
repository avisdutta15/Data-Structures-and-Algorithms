#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
	You should preserve the original relative order of the nodes in each of the two partitions.

	Examples:
	---------
	Input: head = [1,4,3,2,5,2], x = 3
	Output: [1,2,2,4,3,5]
	
	Example 2:
	Input: head = [2,1], x = 2
	Output: [1,2]

	Approach:
	---------
	Iterate the list and segregate the nodes into two halves based on the value < x.
	lefthalf < x <= righthalf
	at the end join both the halves and return.
	Note: x will lie in the right half
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
	ListNode* partition(ListNode* head, int x) {
		if (head == nullptr || head->next==nullptr)
			return head;

		ListNode* leftHead = nullptr, * leftTail = nullptr;
		ListNode* rightHead = nullptr, * rightTail = nullptr;

		ListNode* current = head;
		while (current != nullptr) {
			if (current->data < x) {
				if (leftHead == nullptr) {
					leftHead = current;
					leftTail = current;
				}
				else {
					leftTail->next = current;
					leftTail = leftTail->next;
				}
			}
			else {
				if (rightHead == nullptr) {
					rightHead = current;
					rightTail = current;
				}
				else {
					rightTail->next = current;
					rightTail = rightTail->next;
				}
			}	
			current = current->next;
		}


		//if x is smaller than all the elements in the list
		//left list will not exist. return the right list (which is the original list) as it is 
		if (leftHead == nullptr) {
			return rightHead;
		}
		//if x is greater than all the elements in the list
		//right list will not exist. return the left list (which is the original list) as it is 
		else if (rightHead == nullptr) {
			return leftHead;
		}
		//if x exists in the list, we will have left and right list.
		//connect both of them and make the righttail->next = nullptr. return left head.
		else {
			leftTail->next = rightHead;
			rightTail->next = nullptr;
			return leftHead;
		}
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

	ListNode* head = new ListNode(1);
	head->next = new ListNode(4);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(2);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(2);

	cout << "Original List: ";
	printList(head);

	ListNode* newHead = obj.partition(head, 3);

	cout << "List After Partition: ";
	printList(newHead);

	return 0;
}