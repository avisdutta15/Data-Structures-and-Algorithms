#include <iostream>
using namespace std;

/*
    Problem Statement:
    Given a singly linked list, the task is to remove all the nodes with any node on their right whose value is 
    greater and return the head of the modified linked list.
    
    Examples:
    ---------
    Input: head: 12->15->10->11->5->6->2->3
    Output: 15->11->6->3
    Explanation: Node with value 12 , 10, 5, and 2 will be deleted as the greater value is present on right side of nodes.
    
    Input: head: 10->20->30->40->50->60
    Output: 60
    Explanantion: Node with value 10 , 20, 30, 40 and 50 will be deleted as the greater value is present on right side of nodes.

    Approach:
    We need to delete the nodes such that the resulting list contains nodes which are decreasing in value. 
    1. Recursive
    Do a recursion. At the tail return the last node. Compare the current node with the maxTillNow.
    If the current node data < maxTillNow then it means we need to delete the current node. so delete the current node 
    and return the next node that was returned from recursion.

    2. Iterative
    The idea is to reverse the linked list and maintain the maximum value from left side. 
    Since we reversed the list, the deletion of an element becomes easier (node_prev->next = node->next). 
    If value of current node is greater than maximum value from left, then update the max value and move to next node. 
    Otherwise, delete the current node. 
    Reverse the resultant list and return it. 

*/

struct LinkedListNode {
    int data;
    LinkedListNode* next = nullptr;
    LinkedListNode(int data = 0, LinkedListNode* next = nullptr) : data(data), next(next) {}
};

class LinkedList {
private:
    LinkedListNode* head, * tail;
    LinkedListNode* deleteNodesWithGreaterValuesOnRightUtil(LinkedListNode*& node, int& maxTillNow) {
        if (node->next == nullptr) {
            maxTillNow = node->data;
            return node;
        }

        LinkedListNode* nextNode = deleteNodesWithGreaterValuesOnRightUtil(node->next, maxTillNow);
        LinkedListNode* nodeToReturn = nullptr;

        //Compare the current node data with the maxTillNow.
        //if current node < maxTillNow that means it has greater nodes to its right. so delete it.
        if (node->data < maxTillNow) {
            delete node;
            node = nullptr;
            nodeToReturn = nextNode;
        }
        else {
            maxTillNow = node->data;
            node->next = nextNode;
            nodeToReturn = node;
        }
        return nodeToReturn;
    }

    void reverseList(LinkedListNode*& head) {
        LinkedListNode* prev = nullptr;
        LinkedListNode* current = head;
        LinkedListNode* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

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

    void deleteNodesWithGreaterValuesOnRightRecursive() {
        LinkedListNode* currentNode = head;
        int maxTillNow = INT_MIN;
        head = deleteNodesWithGreaterValuesOnRightUtil(currentNode, maxTillNow);
    }

    void deleteNodesWithGreaterValuesOnRightIterative() {
        reverseList(head);

        int maxTillNow = head->data;
        LinkedListNode* current = head->next, *prev= head;
        LinkedListNode* nextNode = nullptr;
        while (current != nullptr) {
            //if current is less than maxTillNow then delete it else leave it as it is
            if (current->data < maxTillNow) {
                prev->next = current->next;
                nextNode = current->next;
                delete current;
                current = nullptr;
                current = nextNode;
            }
            else {
                maxTillNow = current->data;
                prev = current;
                current = current->next;
            }
        }

        reverseList(head);
    }
};

int main() {
    cout << "Recursive Approach: " << endl;
    //Test 1: 12->15->10->11->5->6->2->3
    //O/P:    15->11->6->3
    LinkedList* list1 = new LinkedList();
    list1->push_back(12);
    list1->push_back(15);
    list1->push_back(10);
    list1->push_back(11);
    list1->push_back(5);
    list1->push_back(6);
    list1->push_back(2);
    list1->push_back(3);

    list1->printList();
    cout << endl;

    list1->deleteNodesWithGreaterValuesOnRightRecursive();
    list1->printList();
    cout << endl;


    //Test 2: 10->20->30->40->50->60
    //O/P:    60
    LinkedList* list2 = new LinkedList();
    list2->push_back(10);
    list2->push_back(20);
    list2->push_back(30);
    list2->push_back(40);
    list2->push_back(50);
    list2->push_back(60);

    list2->printList();
    cout << endl;

    list2->deleteNodesWithGreaterValuesOnRightRecursive();
    list2->printList();
    cout << endl;

    cout << "Iterative Approach: " << endl;
    //Test 1: 12->15->10->11->5->6->2->3
    //O/P:    15->11->6->3
    LinkedList* list3 = new LinkedList();
    list3->push_back(12);
    list3->push_back(15);
    list3->push_back(10);
    list3->push_back(11);
    list3->push_back(5);
    list3->push_back(6);
    list3->push_back(2);
    list3->push_back(3);

    list3->printList();
    cout << endl;

    list3->deleteNodesWithGreaterValuesOnRightIterative();
    list3->printList();
    cout << endl;


    //Test 2: 10->20->30->40->50->60
    //O/P:    60
    LinkedList* list4 = new LinkedList();
    list4->push_back(10);
    list4->push_back(20);
    list4->push_back(30);
    list4->push_back(40);
    list4->push_back(50);
    list4->push_back(60);

    list4->printList();
    cout << endl;

    list4->deleteNodesWithGreaterValuesOnRightIterative();
    list4->printList();
    cout << endl;
    return 0;
}