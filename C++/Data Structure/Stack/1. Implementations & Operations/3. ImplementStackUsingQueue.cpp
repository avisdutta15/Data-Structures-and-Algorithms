#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	A stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle.
	It can be implemented using an Q by treating the end of the Q as the top of the stack.
	To push into the stack, push all the element at the end of the Q.
	To pop from the stack, push all the elements to the end of the Q leaving the top element as it is.

	Examples:
	---------
	
	Approach:
	---------
	Method 1: Using a Single Queue (Push operation is O(N))
	This method ensures that the most recently added element is always at the front of the queue, 
	making pop and top operations efficient (O(1)). 
		push(x): The new element x is added to the rear of the queue. To make it the "top" of the stack, 
				 all preceding elements are moved one by one from the front to the rear of the queue. 
				 This effectively rotates the queue, placing x at the front.
		pop(): Since the "top" element is always at the front of the queue, popleft() directly removes and returns it.
		top(): Returns the element at the front of the queue without removing it. 
		empty(): Checks if the queue is empty.
	
	Method 2: Using Two Queues (Pop operation is O(N))
	This method ensures that the most recently added element is always at the end of the queue, 
		push(x): The new element x is added to the rear of the queue. 
		pop(): 	Since the "top" element is always at the end of the queue, all preceding elements are moved one by one 
				from the front to the rear of the queue. This effectively rotates the queue, placing x at the front.
		top(): Returns the element at the back of the queue without removing it. 
		empty(): Checks if the queue is empty.
*/

class Stack {
private:
	int _capacity;
	queue<int> q;
public:
	Stack(int capacity) {
		_capacity = capacity;
	}

	// push the new element at the back of the stack.
	// back of the stack represents the top.
	void push(int x) {
		if (q.size() == _capacity)
			cout << "Stack Overflow" << endl;
		else
			q.push(x);
	}

	// to pop the top element, push all the elements 
	// before it in the Q to the back of the Q.
	// Then pop the top element from the front of the Q
	int pop() {
		if (q.size() == 0) {
			cout << "Stack Underflow" << endl;
			return -1;
		}

		int size = q.size();
		while (size != 1) {
			int x = q.front();
			q.pop();
			q.push(x);
			size--;
		}
		int x = q.front();
		q.pop();
		return x;
	}

	int top() {
		if (q.size() == 0) {
			cout << "Stack Underflow" << endl;
			return -1;
		}
		return q.back();
	}

	bool empty() {
		return q.size() == 0;
	}

	int size() {
		return q.size();
	}
};


//Top = 5
//Pop = 5
//1 2 3 4 5

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