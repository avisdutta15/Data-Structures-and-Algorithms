#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes 
	of the list from position left to position right, and return the reversed list.

 

	Examples: 
	--------
	Input: head = [1,2,3,4,5], left = 2, right = 4
	Output: [1,4,3,2,5]

	Example 2:
	Input: head = [5], left = 1, right = 1
	Output: [5]

	Approach:
	---------
	1 -> 2 -> 3 -> 4 -> 5 -> 6 ->NULL    left = 3 right = 5

	we will reverse nodes from index 3 to 5
	5 -> 4 -> 3

	Linking:
	1. Now 3 -> next should be 6.
	current is at 6 after the reversal.
	But we would lose the reference of 3 after the reversal. So store the reference before the reversal starts.
	newTail = current (3)
	{
		reversal
	}

	newTail->next = current;

	2. 2 -> should point to 5 i.e. the new head of the reversed list.
	But we would lose the reference of 2 after reversal. So store the reference before the reversal starts.
	newheadPrev = prev(2)
	{
		reversal
	}
	newHeadPrev->next = prev [because prev is the new head]

	Since we might change the head as well (if left = 1) so create a dummy node and link it to head.
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
	
public:
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		if (head == nullptr)
			return head;

		ListNode* dummyHead = new ListNode(0, head);
		ListNode* current = head, * prev = dummyHead, * next = nullptr;

		int nodeIndex;
		for (nodeIndex = 1; nodeIndex != left && current != nullptr; nodeIndex++) {
			prev = current;
			current = current->next;
		}

		//if the indices are out of bound then return the list as it is
		if (current == nullptr)
			return head;

		//store the references for linking later
		ListNode* newHeadPrev = prev;
		ListNode *newTail = current;
		prev = nullptr;

		//reverse from [left, righ-1]
		while (current != nullptr && nodeIndex != right) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
			nodeIndex++;
		}

		//reverse the right index node
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;

		//now prev is at right
		newHeadPrev->next = prev;

		//link new tail and next
		newTail->next = current;

		return dummyHead->next;
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
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(3);
	head1->next->next->next = new ListNode(4);
	head1->next->next->next->next = new ListNode(5);
	head1->next->next->next->next->next = new ListNode(6);
	printList(head1);

	ListNode* newHead = obj.reverseBetween(head1, 1, 2);
	printList(newHead);
    
	return 0;
}