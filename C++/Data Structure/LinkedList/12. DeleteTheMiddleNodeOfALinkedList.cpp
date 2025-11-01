#include <iostream>
#include <unordered_set>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.

	The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.

	For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.

	Examples:
	--------
	Input: head = [1,3,4,7,1,2,6]
	Output: [1,3,4,1,2,6]
	Explanation:
	The above figure represents the given linked list. The indices of the nodes are written below.
	Since n = 7, node 3 with value 7 is the middle node, which is marked in red.
	We return the new list after removing this node. 

	Input: head = [1,2,3,4]
	Output: [1,2,4]
	Explanation:
	The above figure represents the given linked list.
	For n = 4, node 2 with value 3 is the middle node, which is marked in red.

	Input: head = [2,1]
	Output: [2]
	Explanation:
	The above figure represents the given linked list.
	For n = 2, node 1 with value 1 is the middle node, which is marked in red.
	Node 0 with value 2 is the only node remaining after removing node 1.

	Constraints:
	------------
	The number of nodes in the list is in the range [1, 10^5].
	1 <= Node.val <= 10^5

	Approach:
	--------
	fast and slow pointer. slow will point to middle node. keep a slow prev.
	delete slow and link slowprev->next = slow->next;
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
	ListNode* deleteMiddle(ListNode* head) {
		//if no nodes or one node
		if (head == nullptr || head->next == nullptr) {
			return nullptr;
		}

		//Get the middle node. slow will point to middle node
		ListNode* fast = head, *slow = head, *slowPrev = nullptr;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slowPrev = slow;
			slow = slow->next;
		}

		//if the list is of even size then fastptr == nullptr
		//if the list is of odd size then fastptr == lastnode
		ListNode* nodeTobeDeleted = slow;
		slowPrev->next = slow->next;
		delete(nodeTobeDeleted);
		nodeTobeDeleted = nullptr;
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

	//Test 1 : 1,3,4,7,1,2,6
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(3);
	head1->next->next = new ListNode(4);
	head1->next->next->next = new ListNode(7);
	head1->next->next->next->next = new ListNode(1);
	head1->next->next->next->next->next = new ListNode(2);
	head1->next->next->next->next->next->next = new ListNode(6);
	printList(head1);

	ListNode* newHead = obj.deleteMiddle(head1);
	printList(newHead);

	//Test 2 : 1 2 3 4
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(2);
	head2->next->next = new ListNode(3);
	head2->next->next->next = new ListNode(4);
	printList(head2);

	newHead = obj.deleteMiddle(head2);
	printList(newHead);

	//Test 3
	ListNode* head3 = new ListNode(2);
	head3->next = new ListNode(1);
	printList(head3);

	newHead = obj.deleteMiddle(head3);
	printList(newHead);

	//Test 4
	ListNode* head4 = new ListNode(1);
	printList(head4);

	newHead = obj.deleteMiddle(head4);
	printList(newHead);
	return 0;
}
