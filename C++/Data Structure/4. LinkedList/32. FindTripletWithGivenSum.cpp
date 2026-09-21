#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given three linked lists, say a, b and c, find one node from each list such that the sum of the values of the nodes is equal to a given number. 

	Examples:
	---------
	Input: 
		list 1 : 12->6->29
		list 2 : 23->5->8
		list 3 : 90->20->59
		key : 101
	O/P:   6 -> 5 -> 90

	Approach:
	---------
	A simple method to solve this problem is to run three nested loops. 
	The outermost loop picks an element from list a, the middle loop picks an element from 
	b and the innermost loop picks from c. The innermost loop also checks whether the sum of 
	values of current nodes of a, b and c is equal to given number. The time complexity of 
	this method will be O(n^3).
	Sorting can be used to reduce the time complexity to O(n^2). Following are the detailed steps. 
		1) Sort list b in ascending order, and list c in descending order. 
		2) After the b and c are sorted, one by one pick an element from list a and find the pair by 
		traversing both b and c.
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
	// Why do we have return slow prev in case of even number of nodes?
	// Because in case of even number of nodes, we have 2 middle nodes. We should return the second last
	// middle node to avoid StackOverflow Exception.
	// Suppose we have list {1, 2}
	// We call findMiddleNode(list)
	// We should get 1 as the middle node. If we do not have that condition, we would get 2 as middlenode.
	// If we get 2 as middle node, then leftList {1, 2} and rightList {nullptr}
	// And we would again call the sort on leftList {1, 2} and rightList {nullptr}. 
	// This would cause StackOverflow Exception as leftList is always equals the original list.
	// To fix this in case of even number of nodes e.g. - {1, 2} we have 2 middle nodes.
	// We should return the second last middle node {1}. Then calling sort on leftList {1} and rightList{2}
	// would not give StackOverflow
	ListNode* findMiddleNode(ListNode* head) {
		ListNode* fast = head, * slow = head, * slowPrev = nullptr;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slowPrev = slow;
			slow = slow->next;
		}
		//in case of even number of nodes, get the second last as middle node.
		if (fast == nullptr)
			return slowPrev;

		return slow;
	}

	ListNode* mergeLists(ListNode* list1, ListNode* list2, bool isAscending) {
		if (list1 == nullptr)
			return list2;
		if (list2 == nullptr)
			return list1;
		if (list1 == nullptr && list2 == nullptr)
			return nullptr;

		ListNode* dummyNode = new ListNode(0);
		ListNode* current = dummyNode;

		if (isAscending == true) {
			while (list1 != nullptr && list2 != nullptr) {
				if (list1->data <= list2->data) {
					current->next = list1;
					list1 = list1->next;
				}
				else {
					current->next = list2;
					list2 = list2->next;
				}
				current = current->next;
			}
		}
		else {
			while (list1 != nullptr && list2 != nullptr) {
				if (list1->data >= list2->data) {
					current->next = list1;
					list1 = list1->next;
				}
				else {
					current->next = list2;
					list2 = list2->next;
				}
				current = current->next;
			}
		}

		while (list1 != nullptr) {
			current->next = list1;
			current = current->next;
			list1 = list1->next;
		}

		while (list2 != nullptr) {
			current->next = list2;
			current = current->next;
			list2 = list2->next;
		}

		return dummyNode->next;
	}

	ListNode* mergeSort(ListNode* head, bool isAscending = true) {
		//base case: single node then return
		if (head == nullptr || head->next == nullptr)
			return head;

		//find the middle node
		ListNode* middleNode = findMiddleNode(head);

		//Segregate the lists
		ListNode* leftList = nullptr, * rightList = nullptr;
		leftList = head;
		rightList = middleNode->next;
		middleNode->next = nullptr;

		//Recursively sort each half
		leftList = mergeSort(leftList, isAscending);
		rightList = mergeSort(rightList, isAscending);

		//Merge the two halves
		return mergeLists(leftList, rightList, isAscending);
	}
public:
	vector<int> findTriplet(ListNode* head1, ListNode* head2, ListNode* head3, int key) {
		if (head1 == nullptr || head2 == nullptr || head3 == nullptr)
			return vector<int>{};

		head2 = mergeSort(head2, true);
		head3 = mergeSort(head3, false);
		while (head1 != nullptr) {
			ListNode* currentHead2 = head2, * currentHead3 = head3;
			while (currentHead2 !=nullptr && currentHead3 !=nullptr) {
				if (head1->data + currentHead2->data + currentHead3->data == key) {
					return vector<int>{head1->data, currentHead2->data, currentHead3->data};
				}
				else if (head1->data + currentHead2->data + currentHead3->data < key)
					currentHead2 = currentHead2->next;
				else
					currentHead3 = currentHead3->next;
			}
			head1 = head1->next;
		}
		return vector<int>{};
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
	//	head1 : 12->6->29
	//	head2 : 23->5->8
	//	head3 : 90->20->59
	//	  K	  : 101
	ListNode* head1 = new ListNode(12);
	head1->next = new ListNode(6);
	head1->next->next = new ListNode(29);

	ListNode* head2 = new ListNode(23);
	head2->next = new ListNode(5);
	head2->next->next = new ListNode(8);
	
	ListNode* head3 = new ListNode(90);
	head3->next = new ListNode(20);
	head3->next->next = new ListNode(59);

	printList(head1);
	printList(head2);
	printList(head3);

	auto ans = obj.findTriplet(head1, head2, head3, 101);
	for (int i : ans)
		cout << i << " ";

	return 0;
}