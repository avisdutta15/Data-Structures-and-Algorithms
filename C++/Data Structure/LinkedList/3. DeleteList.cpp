#include <iostream>
using namespace std;

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

    void deleteList() {
        //if list is empty
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        LinkedListNode* current = head;
        while (current != nullptr) {
            LinkedListNode* nodeToDelete = current;
            current = current->next;
            delete(nodeToDelete);
            nodeToDelete = nullptr;
        }
        head = nullptr;
        tail = nullptr;
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

    list->deleteList();

    list->printList();
    cout << endl;

    return 0;
}