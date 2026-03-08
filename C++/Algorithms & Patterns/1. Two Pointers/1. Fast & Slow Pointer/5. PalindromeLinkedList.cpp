#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

	Examples:
	---------
	Input: head = [1,2,2,1]
	Output: true

	Input: head = [1,2]
	Output: false
	
	Approach : TC - O(n) SC - O(1)
    -------------------------------
	The approach involves reversing the second half of the linked list starting from the middle. 
	After reversing, traverse from the headof the list and the head of the reversed second half 
	simultaneously, comparing the node values. If all corresponding nodes have equal values, 
	the list is a palindrome.

*/

struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

// 1 2 1
//   s f
// 1 2 2 1
//     s    f		 
class Solution {
	ListNode* reverse(ListNode* head) {
		ListNode* current = head, * prev = nullptr, * next = nullptr;
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
		return head;
	}

public:
	bool isPalindrome(ListNode* head) {
		if (head == nullptr)
			return false;

		if (head->next == nullptr)
			return true;

		ListNode* slow = head, * fast = head, * slowPrev = nullptr;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slowPrev = slow;
			slow = slow->next;
		}

		//	if fast is nullptr then list is of even size
		//		slow is the start of next list
		//		slowPrev->next = nullptr marks the end of first list.
		//	if fast->next == nullptr then list is of odd size
		//		slow is the middle node. slow->next is the new head.
		//		slowPrev->next = null marks the end of first list.

		ListNode* head2 = nullptr;
		slowPrev->next = nullptr;
		if (fast == nullptr) {
			head2 = slow;
		}
		else {
			head2 = slow->next;
		}

		head2 = reverse(head2);
		ListNode* ptr1 = head, * ptr2 = head2;
		while (ptr1 != nullptr && ptr2 != nullptr) {
			if (ptr1->data != ptr2->data)
				return false;
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}

		return true;
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

	//Test 1 : 1, 2, 2, 1
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(2);
	head1->next->next->next = new ListNode(1);
	printList(head1);

	obj.isPalindrome(head1) == true ? cout << "Palindrome." << endl : cout << "Not Palindrome." << endl;

	//Test 2 : 1 2 3 2 1
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(2);
	head2->next->next = new ListNode(3);
	head2->next->next->next = new ListNode(2);
	head2->next->next->next->next = new ListNode(1);
	printList(head2);

	obj.isPalindrome(head2) == true ? cout << "Palindrome." << endl : cout << "Not Palindrome." << endl;


	//Test 3 : 1 2 3 4
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(2);
	head3->next->next = new ListNode(3);
	head3->next->next->next = new ListNode(4);
	printList(head3);

	obj.isPalindrome(head3) == true ? cout << "Palindrome." << endl : cout << "Not Palindrome." << endl;

	//Test 4 : 1 2 3 4 5
	ListNode* head4 = new ListNode(1);
	head4->next = new ListNode(2);
	head4->next->next = new ListNode(3);
	head4->next->next->next = new ListNode(4);
	head4->next->next->next->next = new ListNode(5);
	printList(head4);

	obj.isPalindrome(head4) == true ? cout << "Palindrome." << endl : cout << "Not Palindrome." << endl;

	return 0;
}
