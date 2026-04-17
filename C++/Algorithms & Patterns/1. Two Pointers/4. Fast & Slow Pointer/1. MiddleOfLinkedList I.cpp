#include <iostream>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a singly linked list, return the middle node of the linked list.
	If there are two middle nodes, return the second middle node.

	Examples:
	---------
	Input: head = [1,2,3,4,5]
	Output: [3,4,5]
	Explanation: The middle node of the list is node 3.

	Input: head = [1,2,3,4,5,6]
	Output: [4,5,6]
	Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

	Approach:
	---------
	We use the Fast and Slow Pointer technique (also known as the "tortoise and hare" algorithm) 
	to find the middle node of the linked list.
	
	How it works:
	- We initialize two pointers: fast and slow, both starting at the head of the linked list.
	- The fast pointer moves two steps at a time, while the slow pointer moves one step at a time.
	- When the fast pointer reaches the end of the list (or becomes nullptr), the slow pointer 
	  will be exactly at the middle node.
	
	Why it works:
	- By the time the fast pointer (moving at 2x speed) reaches the end, the slow pointer 
	  (moving at 1x speed) will have covered half the distance.
	- For odd-length lists: The fast pointer becomes nullptr exactly when slow reaches the middle.
	- For even-length lists: The fast pointer reaches the last node when slow reaches the 
	  first middle node.
	
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
	ListNode* middleNode(ListNode* head) {
		if (head == nullptr)
			return head;

		ListNode* fast = head, * slow = head;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}
};

int main() {
	Solution obj;
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);

	ListNode *middleNode = obj.middleNode(head);
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