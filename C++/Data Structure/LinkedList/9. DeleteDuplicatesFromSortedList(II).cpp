#include <iostream>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
	Return the linked list sorted as well.

	Examples:
	--------
	Input: 1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5 -> NULL
	Output: 1 -> 2 -> 5 -> NULL

	Input: 1 -> 1 -> 1 -> 2 -> 3 -> NULL
	Output: 2 -> 3 -> NULL

	Input: 1 -> 1 -> 1 -> NULL
	Output: Null

	Approach:
	since the duplicate can be head as well. So keep a dummy node. dummy->next = head.
	iterate the list from head
		if current and next are duplicate
			delete all the duplicates (currentnodes)
			current is now at the last duplicate. delete this too.
			link prev and next.
		else
			update prev
			current = current->next
	return dummy->next
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
	ListNode* deleteDuplicatesII(ListNode* head) {
		if (head == nullptr)
			return head;
		
		ListNode* dummyNode = new ListNode(0, head);
		ListNode* currentNode = head, * prevNode = dummyNode; 
		ListNode* nodeToBeDeleted = nullptr;
		while (currentNode != nullptr && currentNode->next != nullptr) {
			//found a duplicate node
			if (currentNode->data == currentNode->next->data) {
				//keep on deleting the duplicate
				while (currentNode->next != nullptr && currentNode->data == currentNode->next->data) {
					nodeToBeDeleted = currentNode;
					currentNode = currentNode->next;
					delete(nodeToBeDeleted);
					nodeToBeDeleted = nullptr;
				}
				//current is not at the last occurence of the duplicate. delete this and link prev and next node.
				nodeToBeDeleted = currentNode;
				currentNode = currentNode->next;
				delete(nodeToBeDeleted);
				nodeToBeDeleted = nullptr;
				prevNode->next = currentNode;
			}
			else {
				prevNode = currentNode;
				currentNode = currentNode->next;
			}
		}

		return dummyNode->next;
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

	//Test 1
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(1);
	head1->next->next = new ListNode(2);
	printList(head1);

	ListNode* newHead = obj.deleteDuplicatesII(head1);
	printList(newHead);

	//Test 2
	ListNode* head2 = new ListNode(1);
	head2->next = new ListNode(1);
	head2->next->next = new ListNode(2);
	head2->next->next->next = new ListNode(3);
	head2->next->next->next->next = new ListNode(3);
	printList(head2);

	newHead = obj.deleteDuplicatesII(head2);
	printList(newHead);

	//Test 3
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(1);
	head3->next->next = new ListNode(2);
	head3->next->next->next = new ListNode(2);
	printList(head3);

	newHead = obj.deleteDuplicatesII(head3);
	printList(newHead);
	
	//Test 4
	ListNode* head4 = new ListNode(1);
	head4->next = new ListNode(1);
	head4->next->next = new ListNode(1);
	head4->next->next->next = new ListNode(1);
	printList(head4);

	newHead = obj.deleteDuplicatesII(head4);
	printList(newHead);
	return 0;
}



/*
	sorse tel
	maggie (ata)
	oats
	biscuit
	sugar
	sweet corn (frozen)
	dal
	gota suknolonka
*/

