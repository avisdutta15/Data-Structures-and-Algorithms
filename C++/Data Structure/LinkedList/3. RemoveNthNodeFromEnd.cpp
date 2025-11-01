#include <iostream>
using namespace std;

struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (head == nullptr)
			return nullptr;

		int index = 0;
		ListNode* currentNode = head;
		while (currentNode != nullptr && index < n-1) {
			currentNode = currentNode->next;
			index++;
		}

		ListNode* nthNodeFromEnd = head;
		ListNode* nthNodeFromEndPrev = nullptr;
		while (currentNode->next != nullptr) {
			nthNodeFromEndPrev = nthNodeFromEnd;
			nthNodeFromEnd = nthNodeFromEnd->next;
			currentNode = currentNode->next;
		}

		//only one node and n == 1
		//n = size of the list i.e. nth node from = head - then delete the head and update head
		//n = any other node then delete that node and update previous_node -> next
		if (head->next == nullptr && n == 1) {
			delete(head);
			head = nullptr;
		}
		else if (nthNodeFromEnd == head) {
			ListNode* nodeToDelete = head;
			head = head->next;
			delete(nodeToDelete);
			nodeToDelete = nullptr;
		}
		else {
			nthNodeFromEndPrev->next = nthNodeFromEnd->next;
			delete(nthNodeFromEnd);
			nthNodeFromEnd = nullptr;
		}

		return head;
	}
};

void printList(ListNode* node) {
	if (node == nullptr) {
		cout << "List is empty."<<endl;
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
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(3);
	head1->next->next->next = new ListNode(4);
	head1->next->next->next->next = new ListNode(5);
	printList(head1);

	cout << "Removing 2nd node from end" << endl;
	ListNode* newHead = obj.removeNthFromEnd(head1, 2);
	printList(newHead);

	//Test 2
	ListNode* head2 = new ListNode(1);
	printList(head2);

	cout << "Removing 1st node from end" << endl;
	newHead = obj.removeNthFromEnd(head2, 1);
	printList(newHead);

	//Test 3
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(2);
	printList(head3);

	cout << "Removing 1st node from end" << endl;
	newHead = obj.removeNthFromEnd(head3, 1);
	printList(newHead);


	//Test 4
	ListNode* head4 = new ListNode(1);
	head4->next = new ListNode(2);
	printList(head4);

	cout << "Removing 2nd node from end" << endl;
	newHead = obj.removeNthFromEnd(head4, 2);
	printList(newHead);

	return 0;
}