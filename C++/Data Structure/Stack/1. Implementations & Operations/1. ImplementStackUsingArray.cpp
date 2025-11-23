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
	It can be implemented using an array by treating the end of the array as the top of the stack.

	Examples:
	---------

	Approach:
	---------

*/

class Stack {
private:
	int _capacity;
	int _size;
	int* array;
public:
	Stack(int capacity) {
		_capacity = capacity;
		_size = -1;
		array = new int[_capacity];
	}

	void push(int x) {
		if (_size == _capacity - 1)
			cout << "Stack Overflow" << endl;
		else
			array[++_size] = x;
	}

	int pop() {
		if (_size == -1) {
			cout << "Stack Underflow" << endl;
			return -1;
		}
		return array[_size--];
	}

	int top() {
		if (_size == -1) {
			cout << "Stack Underflow" << endl;
			return -1;
		}
		return array[_size];
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