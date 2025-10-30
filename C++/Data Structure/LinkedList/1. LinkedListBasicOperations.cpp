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

    void push_front(int data) {
        LinkedListNode* node = new LinkedListNode(data);

        //if list is empty
        if (head == nullptr) {
            head = node;
            tail = node;
        } 
        else{
            node->next = head;
            head = node;
        }
    }

    int pop_front() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return -1;
        }
        
        int result = -1;
        //if only 1 element
        if (head->next == nullptr) {
            result = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            result = head->data;
            LinkedListNode* nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;
        }
        return result;
    }

    int pop_back() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return -1;
        }

        int result = -1;
        //if only 1 element
        if (head->next == nullptr) {
            result = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            result = tail->data;
            LinkedListNode* tailPrev = head;
            while (tailPrev->next != tail)
                tailPrev = tailPrev->next;
            delete tail;
            tail = nullptr;
            tailPrev->next = nullptr;
            tail = tailPrev;
        }
        return result;
    }

    void deleteList() {
        if (head == nullptr)
            return;

        LinkedListNode* currentNode = head;
        while (currentNode != nullptr) {
            LinkedListNode* nodeToDelete = currentNode;
            currentNode = currentNode->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;
        }
        head = nullptr;
        tail = nullptr;
    }

    bool searchKey(int data) {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return false;
        }

        LinkedListNode* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == data)
                return true;
            currentNode = currentNode->next;
        }
        return false;
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
};

int main() {
    LinkedList* list = new LinkedList();
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);
    list->push_front(5);
    list->push_front(2);

    //Test 1 : List not empty. Print list
    cout << endl;
    list->printList();
    cout << endl;

    //Test 2: List not empty. Search Key Present
    list->searchKey(10) == true ? cout << "Found key: " << 10 << endl : cout << "Not Found Key: " << 10 << endl;

    //Test 3: List not empty. Search Key Present
    list->searchKey(100) == true ? cout << "Found key: " << 100 << endl : cout << "Not Found Key: " << 100 << endl;
    
    //Test 4: Delete Keys one by one
    cout << "Deleted: "<< list->pop_front() << endl;
    cout << "Deleted: "<< list->pop_front() << endl;
    cout << "Deleted: "<< list->pop_back() << endl;
    cout << "Deleted: "<< list->pop_back() << endl;
    cout << "Deleted: "<< list->pop_back() << endl;
    cout << "Deleted: "<< list->pop_back() << endl;

    list->printList();

    //Test 5: Add data to empty list
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    list->push_front(5);
    list->push_front(2);

    list->printList();

    //Test 6: Delete whole List
    list->deleteList();
    cout << endl;
    list->printList();

    return 0;
}