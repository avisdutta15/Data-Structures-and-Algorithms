#include <iostream>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a linked list, return the node where the cycle begins. 
	If there is no cycle, return null.

	There is a cycle in a linked list if there is some node in the list that can be 
	reached again by continuously following the next pointer. Internally, pos is used 
	to denote the index of the node that tail's next pointer is connected to (0-indexed). 
	It is -1 if there is no cycle. Note that pos is not passed as a parameter.

	Do not modify the linked list.


	Examples:
	---------
	Input: head = [3,2,0,-4], pos = 1
	Output: tail connects to node index 1
	Explanation: There is a cycle in the linked list, where tail connects to the second node.

	Input: head = [1,2], pos = 0
	Output: tail connects to node index 0
	Explanation: There is a cycle in the linked list, where tail connects to the first node.

	Input: head = [1], pos = -1
	Output: no cycle
	Explanation: There is no cycle in the linked list.

	Approach:
	---------
	We use the Fast and Slow Pointer technique (also known as the "tortoise and hare" algorithm)
	to detect cycle in the linked list.

	Time Complexity: O(N) - We traverse the list only once.
	Space Complexity: O(1) - We use only two pointers regardless of input size.


*/

struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int x) : data(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : data(x), next(next) {}
};

class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		if (head == nullptr)
			return head;

		// if the list has only one node then return false.
		// this explicit check is needed because at the end of
		// the while loop, fast and slow will be at head. And
		// as they are same, the algo will detect it as a loop which is wrong.
		if (head->next == nullptr)
			return nullptr;

		ListNode* fast = head, * slow = head;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;

			// if both collides then its a cyclce. so break from loop
			if (fast == slow)
				break;
		}

		// if fast and slow did not meet then return false
		if (fast != slow)
			return nullptr;

		// reset one of the pointer to head and walk 1 step at a time until they meet
		// meeting point is the start of the cycle
		fast = head;
		while (fast != slow) {
			fast = fast->next;
			slow = slow->next;
		}

		return fast;
	}
};


int main() {
	Solution obj;
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);

	ListNode* middleNode = obj.middleNode(head);
	if (middleNode != nullptr) {
		cout << middleNode->data << endl;
	}

	head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(6);

	middleNode = obj.middleNode(head);
	if (middleNode != nullptr) {
		cout << middleNode->data << endl;
	}

	return 0;
}