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

			//if both collides then its a cycle. so break from loop
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

	ListNode* removeCycle(ListNode* head){
		// list is empty
		if (head == nullptr)
			return nullptr;

		// list has 1 node
		if (head->next == nullptr)
			return nullptr;

		// has cycle?
		ListNode *slow = head, *fast = head;
		while(fast!=nullptr && fast->next!=nullptr){
			slow = slow->next;
			fast = fast->next->next;
			if(slow == fast)
				break;
		}

		// if no cycle then return the list as it is
		if(fast != slow){
			return head;
		}

		// Reset one of the pointer to head and walk 1 step at a time until they meet
		// Meeting point is the start of the cycle
		slow = head;
		ListNode *fastPrev = nullptr;
		while (fast != slow) {
			fastPrev = fast;
			fast = fast->next;
			slow = slow->next;
		}

		// fastPrev points to the last node in the cycle.
		fastPrev->next = nullptr;
		return head;
	}
};