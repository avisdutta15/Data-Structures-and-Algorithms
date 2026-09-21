#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given k sorted linked lists of different sizes, we need to merge them into a single list while maintaining their sorted order.


	Examples:
	---------
	Input: 
			head1->1->3->5->7
			head2->2->4->6->8
			head3->0->9->10->11

	O/P:	0->1->2->3->4->5->6->7->8->9->10->11->null

	Approach:
	---------
	The idea is to use a min heap to efficiently track the smallest element among all lists at any given time by initially 
	storing the first node from each list in the heap, then repeatedly extracting the minimum element to build the merged 
	list while adding the next node from that same list to maintain the heap's role in finding the next smallest element.
	
	Time Complexity: O(n * log k) , where n is the total number of nodes from all lists.
	Auxiliary Space: O(k), due to heap. There are at most k elements at any instant.
*/

class ListNode {
public:
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class Solution {
private:
	class Compare {
	public:
		bool operator()(ListNode *a, ListNode *b) {
			if (a->data >= b->data) {
				return true;
			}
			return false;
		}
	};

public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue <ListNode *, vector<ListNode *>, Compare> pq;

		//insert first k rows into pq
		for (int rowId = 0; rowId < lists.size(); rowId++) {
			pq.push(lists[rowId]);
		}

		ListNode* dummyHead = new ListNode(0);
		ListNode* tail = dummyHead;
		while (!pq.empty()) {
			ListNode* node = pq.top();
			pq.pop();

			tail->next = node;
			tail = tail->next;

			if (node->next != nullptr)
				pq.push(node->next);
		}

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

	//Test 1 : 
	//	1->3->5->7
	//	2->4->6->8
	//	0->9->10->11
	//O/P:	0->1->2->3->4->5->6->7->8->9->10->11->null
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(3);
	head1->next->next = new ListNode(5);
	head1->next->next->next = new ListNode(7);

	ListNode *head2 = new ListNode(2);
	head2->next = new ListNode(4);
	head2->next->next = new ListNode(6);
	head2->next->next->next = new ListNode(8);

	ListNode* head3 = new ListNode(0);
	head3->next = new ListNode(9);
	head3->next->next = new ListNode(10);
	head3->next->next->next = new ListNode(11);

	printList(head1);
	printList(head2);
	printList(head3);

	vector<ListNode*> arr = { head1, head2, head3 };
	
	ListNode* newHead = obj.mergeKLists(arr);
	printList(newHead);
	
	return 0;
}