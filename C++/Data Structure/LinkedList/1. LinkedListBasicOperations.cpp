#include <iostream>
using namespace std;

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

	//Add data to the beginning of the list
	void push_front(int data) {
		//Create the node
		ListNode* node = new ListNode(data);

		//if list is empty - make it the head and tail
		if (head == nullptr) {
			head = node;
			tail = head;
		}
		//else - make it head
		else {
			node->next = head;
			head = node;
		}
	}

	//Search key
	bool search_key(int key) {
		if (head == nullptr) {
			cout << "List is empty." << endl;
			return false;
		}
		ListNode* currentNode = head;
		while (currentNode != nullptr && currentNode->data != key) {
			currentNode = currentNode->next;
		}
		//if found then return true else node came outside list so return false.
		return currentNode == nullptr ? false : true;
	}

	//Delete data from the back of the list
	int pop_back() {
		//base case - list is empty. Return
		if (head == nullptr) {
			cout << "Nothing to delete. List is empty" << endl;
			return -1;
		}
		int result = tail->data;

		//if list has only one node then update the head and tail to null
		if (head == tail) {
			delete(head);
			head = nullptr;
			tail = nullptr;
		}
		else {
			//else delete the tail and make the tailprev the new tail
			ListNode* currentNode = head;
			while (currentNode->next != tail) {
				currentNode = currentNode->next;
			}
			//current node is now tail prev
			currentNode->next = nullptr;

			delete(tail);
			tail = nullptr;

			tail = currentNode;
		}

		return result;
	}

	//Delete data from the beginning of the list
	int pop_front() {
		//base case - list is empty
		if (head == nullptr) {
			cout << "Nothing to delete. List is empty" << endl;
			return -1;
		}

		int result = head->data;
		//if list has only one node then update the head and tail to null
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			ListNode* nodeToDelete = head;
			head = head->next;
			delete(nodeToDelete);
			nodeToDelete = nullptr;
		}

		return result;
	}

	//Delete list
	void deleteList() {
		if (head == nullptr) {
			cout << "Nothing to delete. List is empty." << endl;
			return;
		}
		ListNode* currentNode = head;
		ListNode* nodeToDelete = nullptr;
		while (currentNode != nullptr) {
			nodeToDelete = currentNode;
			currentNode = currentNode->next;
			delete(nodeToDelete);
			nodeToDelete = nullptr;
		}

		head = nullptr;
		tail = nullptr;
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

int main() {
	//Test push back
	LinkedList* list1 = new LinkedList();
	list1->push_back(10);
	list1->push_back(20);
	list1->push_back(30);
	list1->push_back(40);
	list1->printList();
	list1->search_key(10) == true ? cout<<"Key 10 found!"<<endl : cout<<"Key 10 not found!"<<endl;
	list1->search_key(100) == true ? cout<<"Key 100 found!"<<endl : cout<<"Key 100 not found!"<<endl;

	//Test pop_back
	LinkedList* list2 = new LinkedList();
	list2->push_back(100);
	list2->push_back(200);
	list2->push_back(300);
	list2->push_back(400);
	list2->printList();

	cout << "Deleting last element : " << list2->pop_back() << endl;
	cout << "Deleting last element : " << list2->pop_back() << endl;
	cout << "Deleting last element : " << list2->pop_back() << endl;
	cout << "Deleting last element : " << list2->pop_back() << endl;
	cout << "Deleting last element : " << list2->pop_back() << endl;

	//Test pop_front
	LinkedList* list3 = new LinkedList();
	list3->push_back(1);
	list3->push_back(2);
	list3->push_back(3);
	list3->push_back(4);
	list3->printList();

	cout << "Deleting first element : " << list3->pop_front() << endl;
	cout << "Deleting first element : " << list3->pop_front() << endl;
	cout << "Deleting first element : " << list3->pop_front() << endl;
	cout << "Deleting first element : " << list3->pop_front() << endl;
	cout << "Deleting first element : " << list3->pop_front() << endl;

	//Test delete list
	LinkedList* list4 = new LinkedList();
	list4->push_back(1000);
	list4->push_back(2000);
	list4->push_back(3000);
	list4->push_back(4000);
	list4->printList();
	list4->deleteList();
	list4->search_key(1000) == true ? cout << "Key 1000 found!" << endl : cout << "Key 1000 not found!" << endl;
	list4->deleteList();
	list4->printList();

	return 0;
}
