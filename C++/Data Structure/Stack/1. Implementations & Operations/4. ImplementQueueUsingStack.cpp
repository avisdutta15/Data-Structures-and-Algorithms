#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
	Problem Statement:
	-----------------
	Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should
	support all the functions of a normal queue (push, peek, pop, and empty).

	Implement the MyQueue class:

	void push(int x) Pushes element x to the back of the queue.
	int pop() Removes the element from the front of the queue and returns it.
	int peek() Returns the element at the front of the queue.
	boolean empty() Returns true if the queue is empty, false otherwise.
	Notes:

	You must use only standard operations of a stack, which means only push to top, peek/pop from top,
	size, and is empty operations are valid.
	Depending on your language, the stack may not be supported natively. You may simulate a stack using
	a list or deque (double-ended queue) as long as you use only a stack's standard operations.

	Examples:
	---------
	Input
	["MyQueue", "push", "push", "peek", "pop", "empty"]
	[[], [1], [2], [], [], []]
	Output
	[null, null, null, 1, 1, false]

	Explanation
	MyQueue myQueue = new MyQueue();
	myQueue.push(1); // queue is: [1]
	myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
	myQueue.peek();  // return 1
	myQueue.pop();   // return 1, queue is [2]
	myQueue.empty(); // return false


	Constraints:

	1 <= x <= 9
	At most 100 calls will be made to push, pop, peek, and empty.
	All the calls to pop and peek are valid.


	Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity?
	In other words, performing n operations will take overall O(n) time even if one of those operations
	may take longer.

	Approach:
	--------
	Approach 1:
		Stack1 bottom has the last inserterd element. -> Queue rear
		Stack1 top has the first inserted element.      -> Queue front
		Stack2 is used to store element temporarily during enqueue op.

		Enqueue(x) - move all the elements from stack1 to stack2.
						push the x to stack1.
						move back all the elements from stack2 to stack1.
						O(N) + O(1) + O(N) = O(N)
		Dequeue()  - stack1.pop()
						O(1)
		Front()     - stack1.top()
						O(1)
		Size()       - stack1.size()
						O(1)

	Approach2:
		Stack1 is used as Input stack. Enqueue happens in stack1.
		Stack2 is used as Output Stack. Dequeue and Front happens in stack2.
		Stack2 top is used as Queue.Front

		Enqueue(x) - push into stack1
						O(1)
		Dequeue()  - if stack2 is empty
							move all elements from stack1 to stack2
						stack2.pop
						Amortized O(1), Worst-case O(n)
						=> Worst-case: All elements from s1 are moved to s2 O(n).
						=> Amortized: Each element is moved at most once from
										 s1 to s2 O(1) per operation.
		Front()     - if stack2 is empty
							move all elements from stack1 to stack2
						stack2.top
						Similar to Dequeue Amortized O(1), Worst-case O(n)
		Size()       - stack1.size() + stack2.size()
						O(1)

	1 Stack
	Approach3:
		Stack bottom represents Queue.front() and Stack.top() is Queue.Rear()

		Enqueue(x) - push into stack. O(1)
		Dequeue()  - Recursively pop elements from the stack.
						Then insert it back to the stack. While inserting back, donot
						insert the last popped element.

						dequeue():
							   if(stack.empty())
									return queue underflow
								int x = stack.top();
								stack.pop();

								//skip for last element
								if(stack.empty())
									return;

								dequeue();
								stack.push(x);
						 O(N)
		Front()     - Recursively pop from the stack. Then insert into the stack.
						Return the popped element.

						int front():
							if(stack.empty())
								return
							int x = stack.top()
							stack.pop()

							if(stack.empty())
								stack.push(x);
								return x;

							int topelement = front()
							stack.push(x);
							return topelement
						 O(N)

*/

class MyQueue1 {
	stack<int> stack1, stack2;
public:
	MyQueue1() {

	}

	void push(int x) {
		while (!stack1.empty()) {
			stack2.push(stack1.top());
			stack1.pop();
		}
		stack1.push(x);
		while (!stack2.empty()) {
			stack1.push(stack2.top());
			stack2.pop();
		}
	}

	int pop() {
		if (stack1.size() != 0) {
			int topElement = stack1.top();
			stack1.pop();
			return topElement;
		}
		return -1;
	}

	int peek() {
		if (stack1.size() != 0)
			return stack1.top();
		return -1;
	}

	bool empty() {
		return stack1.empty();
	}
};

class MyQueue2 {
	stack<int> input, output;
public:
	MyQueue2() {

	}

	void push(int x) {
		input.push(x);
	}

	int pop() {
		if (empty() == true)
			return -1;
		if (output.empty()) {
			while (!input.empty()) {
				output.push(input.top());
				input.pop();
			}
		}
		int topElement = output.top();
		output.pop();
		return topElement;
	}

	int peek() {
		if (empty() == true)
			return -1;
		if (output.empty()) {
			while (!input.empty()) {
				output.push(input.top());
				input.pop();
			}
		}
		int topElement = output.top();
		return topElement;
	}

	bool empty() {
		return input.empty() && output.empty();
	}
};

class MyQueue3 {
	stack<int> stack;
public:
	MyQueue3() {

	}

	void push(int x) {
		if (stack.empty()) {
			stack.push(x);
			return;
		}
		int i = stack.top();
		stack.pop();
		push(x);
		stack.push(i);
	}

	int pop() {
		if (stack.size() != 0) {
			int topElement = stack.top();
			stack.pop();
			return topElement;
		}
		return -1;
	}

	int peek() {
		if (stack.size() != 0)
			return stack.top();
		return -1;
	}

	bool empty() {
		return stack.empty();
	}
};

int main() {
	MyQueue1 myQueue1;
	myQueue1.push(1); // queue is: [1]
	myQueue1.push(2); // queue is: [1, 2] (leftmost is front of the queue)
	cout << myQueue1.peek() << endl;  // return 1
	cout << myQueue1.pop() << endl;   // return 1, queue is [2]
	myQueue1.empty() == true ? cout << "Empty" << endl : cout << "Not Empty" << endl; // return false


	MyQueue2 myQueue2;
	myQueue2.push(1); // queue is: [1]
	myQueue2.push(2); // queue is: [1, 2] (leftmost is front of the queue)
	cout << myQueue2.peek() << endl;  // return 1
	cout << myQueue2.pop() << endl;   // return 1, queue is [2]
	myQueue2.empty() == true ? cout << "Empty" << endl : cout << "Not Empty" << endl; // return false

	MyQueue3 myQueue3;
	myQueue3.push(1); // queue is: [1]
	myQueue3.push(2); // queue is: [1, 2] (leftmost is front of the queue)
	cout << myQueue3.peek() << endl;  // return 1
	cout << myQueue3.pop() << endl;   // return 1, queue is [2]
	myQueue3.empty() == true ? cout << "Empty" << endl : cout << "Not Empty" << endl; // return false
	return 0;
}