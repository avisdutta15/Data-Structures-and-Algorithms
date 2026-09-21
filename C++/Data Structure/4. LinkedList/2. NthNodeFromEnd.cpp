#include <iostream>
using namespace std;

/*
	Problem Statement:
	Given a Linked List of M nodes and a number N, find the value at the Nth node from the end of the Linked List.
	If there is no Nth node from the end, print -1.

	Example:
	-------
	Input: 1 -> 2 -> 3 -> 4, N = 3
	Output: 2
	Explanation: Node 2 is the third node from the end of the linked list.

	Input: 35 -> 15 -> 4 -> 20, N = 4
	Output: 35
	Explanation: Node 35 is the fourth node from the end of the linked list.

	Approach:
	The idea is to maintain two pointers, say ptr1 and ptr2 point to the head of Linked List
	and move ptr1 to the Nth node from the head to ensure that the distance between ptr2 and
	ptr1 is (N - 1).
	Now, move both the pointers simultaneously until ptr1 reaches the last node.
	Since the distance between ptr1 and ptr2 is (N - 1), so when ptr1 will reach the last node,
	ptr2 will reach Nth node from the end of Linked List. Return the value of node pointed by ptr1.

    Example:
    List: 1 2 3 4
    n = 3 i.e. 3rd node from end
    As per our approach we need to maintain a gap of n-1 i.e. 2
    1 2 = 1st gap
    2 3 = 2nd gap
    so move ptr1 till element 3 and wait.
    now move both ptr1 and ptr2=head till we reach the last node.
    1     2    3    4
    p2         p1
          p2        p1
    now p2 is standing at the 3rd node from end.

    Example2:
    List: 1 2 3 4
    n = 1 i.e. 1st node from end
    maintain a gap of n-1 i.e. 0 between p1 and p2
    so p1 and p2 points to 1
    1   2   3   4
    p1
    p2
        p1
        p2
            p1
            p2  
                p1
                p2
    Now p2 points to nth node from end.
*/

struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class LinkedList {
	ListNode* head;
	ListNode* tail;
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	//Add data to the back of the list
	void push_back(int data) {
		//if list is empty
		if (head == nullptr) {
			head = new ListNode(data);
			tail = head;
		}
		else {
			//else add it at back
			tail->next = new ListNode(data);
			tail = tail->next;
		}
	}

	//Property to get the head node
	ListNode* getHeadNode() {
		return head;
	}

	//Print the entire list
	void printList() {
		if (head == nullptr) {
			cout << "Nothing to print. List is empty" << endl;
			return;
		}

		ListNode* currentNode = head;
		while (currentNode != nullptr) {
			cout << currentNode->data << " ";
			currentNode = currentNode->next;
		}
		cout << endl;
	}
};

class Solution {
public:
    ListNode* displayNthFromEnd(ListNode *head, int n) {
        if (head == nullptr)
            return head;

        ListNode* ptr1 = head, * ptr2 = head;
        int index = 1;
        while (ptr1 != nullptr && index != n) {
            ptr1 = ptr1->next;
            index++;
        }
        
        while (ptr1->next != nullptr) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        return ptr2;
    }    
};

int main() {
	LinkedList* list1 = new LinkedList();
	list1->push_back(10);
	list1->push_back(20);
	list1->push_back(30);
	list1->push_back(40);
	list1->printList();

	Solution obj;
	ListNode* nthNode = obj.displayNthFromEnd(list1->getHeadNode(), 1);
	if (nthNode == nullptr) {
		cout << "n is greater than size of list" << endl;
	}
	else {
		cout << "1th node: " << nthNode->data << endl;
	}

	nthNode = obj.displayNthFromEnd(list1->getHeadNode(), 4);
	if (nthNode == nullptr) {
		cout << "n is greater than size of list" << endl;
	}
	else {
		cout << "4th node: " << nthNode->data << endl;
	}

	nthNode = obj.displayNthFromEnd(list1->getHeadNode(), 5);
	if (nthNode == nullptr) {
		cout << "n is greater than size of list" << endl;
	}
	else {
		cout << "5th node: " << nthNode->data << endl;
	}

	return 0;
}