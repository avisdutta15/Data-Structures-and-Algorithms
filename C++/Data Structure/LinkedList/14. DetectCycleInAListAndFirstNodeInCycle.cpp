#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given head, the head of a linked list, determine if the linked list has a cycle in it.
	Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

	Reference:
	----------
	Proof on why the approach works: https://www.youtube.com/watch?v=Cs3KwAsqqn4
	
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
	bool hasCycle(ListNode* head) {
		//if list has no nodes
		if (head == nullptr)
			return false;

		//if list has exactly one node
		if (head->next == nullptr)
			return false;

		ListNode* fast = head, * slow = head;
		while (fast!=nullptr && fast->next != nullptr) {
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

	ListNode* detectCycle(ListNode* head) {
		if (head == nullptr)
			return nullptr;

		if (head->next == nullptr)
			return nullptr;

		ListNode* fast = head, * slow = head;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)
				break;
		}

		//if no cycle
		if (fast != slow)
			return nullptr;

		//reset one of the pointer to head and walk 1 step at a time until they meet
		//meeting point is the start of the cycle
		slow = head;
		while (fast != slow) {
			fast = fast->next;
			slow = slow->next;
		}
		return slow;
	}
};