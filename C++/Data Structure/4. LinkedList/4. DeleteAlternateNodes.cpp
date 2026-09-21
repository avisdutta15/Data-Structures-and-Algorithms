#include <iostream>
using namespace std;

/*
    Problem Statement:
    Given a Singly Linked List, starting from the second node delete all alternate nodes of it. 
    For example, if the given linked list is 1->2->3->4->5 then your function should convert it 
    to 1->3->5, and if the given linked list is 1->2->3->4 then convert it to 1->3.
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

    void deleteAlternateNodes() {
        if (head == nullptr){
            cout << "List is empty." << endl;
            return;
        }

        LinkedListNode* current = head;
        
        while (current != nullptr && current->next!=nullptr) {

            //delete the next node
            LinkedListNode* nodeToDelete = current->next;
            current->next = current->next->next;
            current = current->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;
        }
    }
};

int main() {
    //List of even size
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

    list->deleteAlternateNodes();

    list->printList();
    cout << endl;

    //List of odd size
    LinkedList* list2 = new LinkedList();
    list2->push_back(10);
    list2->push_back(20);
    list2->push_back(30);
    list2->push_back(40);
    list2->push_back(50);
    list2->push_back(60);
    list2->push_back(70);

    list2->printList();
    cout << endl;

    list2->deleteAlternateNodes();

    list2->printList();
    cout << endl;
    return 0;
}