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
*/

struct LinkedListNode {
    int data;
    LinkedListNode* next = nullptr;
    LinkedListNode(int data = 0, LinkedListNode* next = nullptr) : data(data), next(next) {}
};

class LinkedList {
private:
    LinkedListNode* head, * tail;
public:
    LinkedList() {
        //initialize the variables
        head = nullptr;
        tail = head;
    }

    void push_back(int data) {
        LinkedListNode* node = new LinkedListNode(data);

        // if list is empty
        if (head == nullptr) {
            head = node;
        }
        else {
            tail->next = node;
        }
        //update the tail in both cases
        tail = node;
    }

    void printList() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        LinkedListNode* currentNode = head;
        while (currentNode != nullptr) {
            cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
    }    

    int printNthNodeFromEnd(int N) {
        LinkedListNode* ptr1 = head;
        LinkedListNode* ptr2 = head;

        int nodeCount = 1;
        while (ptr1!=nullptr && nodeCount != N){
            ptr1 = ptr1->next;
            nodeCount++;
        }

        //if N doesnot exist then return -1
        if (ptr1 == nullptr)
            return -1;

        while (ptr1->next != nullptr) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        return ptr2->data;
    }
};

int main() {
    LinkedList* list = new LinkedList();
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);
    list->push_back(40);
    list->push_back(50);
    list->push_back(60);
    list->push_back(70);
    list->push_back(80);

    list->printList();
    cout << endl;

    cout << "5th Node from back: " << list->printNthNodeFromEnd(5) << endl;
    cout << "9th Node from back: " << list->printNthNodeFromEnd(100) << endl;

    return 0;
}