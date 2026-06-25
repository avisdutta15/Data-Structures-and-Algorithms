#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	A stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle.
	It can be implemented using an list by treating the head of the list as the top of the stack.

	Examples:
	---------

	Approach:
	---------

*/

struct ListNode {
	int data;
	ListNode* next;
	ListNode(int x) : data(x), next(nullptr) {};
};

class Stack {
private:
	int _capacity;
	int _size;
	ListNode* head;
public:
	Stack(int capacity) {
		_capacity = capacity;
		_size = -1;
		head = nullptr;
	}

	void push(int x) {
		if (_size == _capacity-1) {
			cout << "Stack Overflow" << endl;
			return;
		}
		if (head == nullptr) {
			head = new ListNode(x);
		}
		else {
			ListNode* node = new ListNode(x);
			node->next = head;
			head = node;
		}
		_size++;
	}

	int pop() {
		if (_size == -1) {
			cout << "Stack Underflow" << endl;
			return -1;
		}
		int poppedData = head->data;
		auto nodeToBeDeleted = head;
		head = head->next;
		delete(nodeToBeDeleted);
		nodeToBeDeleted = nullptr;
		_size--;
		return poppedData;
	}

	int top() {
		if (_size == -1) {
			cout << "Stack Underflow" << endl;
			return -1;
		}
		return head->data;
	}

	bool empty() {
		return _size == -1;
	}

	int size() {
		return _size;
	}
};

int main() {
	Stack st(4);

	// pushing elements
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);		//Stack Overflow

	// popping one element
	cout << "Popped: " << st.pop() << "\n";

	// checking top element
	cout << "Top element: " << st.top() << "\n";

	// checking if stack is empty
	cout << "Is stack empty: " << (st.empty() ? "Yes" : "No") << "\n";

	st.pop();	//3
	st.pop();   //2
	st.pop();	//1
	cout << "Popped: " << st.pop() << "\n";		//Stack Underflow

	return 0;
}