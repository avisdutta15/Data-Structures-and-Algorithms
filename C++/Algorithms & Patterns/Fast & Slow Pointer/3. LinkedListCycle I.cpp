#include <iostream>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given head, the head of a linked list, determine if the linked list has a cycle in it.

	There is a cycle in a linked list if there is some node in the list that can be reached again
	by continuously following the next pointer. Internally, pos is used to denote the index of the
	node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

	Return true if there is a cycle in the linked list. Otherwise, return false.

	Examples:
	---------
	Input: head = [3,2,0,-4], pos = 1
	Output: true
	Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).

	Input: head = [1,2], pos = 0
	Output: true
	Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.

	Input: head = [1], pos = -1
	Output: false
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
	bool hasCycle(ListNode* head) {
		if (head == nullptr)
			return false;

		// if the list has only one node then return false.
		// this explicit check is needed because at the end of
		// the while loop, fast and slow will be at head. And
		// as they are same, the algo will detect it as a loop which is wrong.
		if (head->next == nullptr)
			return false;

		ListNode* fast = head, * slow = head;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;

			//if both collides then its a cyclce. so break from loop
			if (fast == slow)
				break;
		}

		//if fast and slow did not meet then return false
		if (fast != slow)
			return false;

		return true;
	}
};


int main() {
	Solution obj;
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = head->next;
	

	
	return 0;
}