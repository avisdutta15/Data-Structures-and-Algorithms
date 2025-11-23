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
	Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    Implement the MinStack class:

    MinStack() initializes the stack object.
    void push(int val) pushes the element val onto the stack.
    void pop() removes the element on the top of the stack.
    int top() gets the top element of the stack.
    int getMin() retrieves the minimum element in the stack.
    You must implement a solution with O(1) time complexity for each function.

	Examples:
	---------
    Input
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]

    Output
    [null,null,null,null,-3,null,0,-2]

    Explanation
    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin(); // return -3
    minStack.pop();
    minStack.top();    // return 0
    minStack.getMin(); // return -2

	Approach:
	---------
    Approach 1 - Keep 2 stacks -
                 main stack & minimum stack.
                 minimum stack stores the mimimum values (monotonically decreasing stack)

    Approach 2 - Keep 1 stack but the stack nodes is <value, minimum_Value)
*/

//Uses 2 Stack - main stack + min stack (monotonically decreasing stack)
// T.C - O(N) S.C. - O(2N)
class MinStack1 {
private:
	stack<int> stck;
	stack<int> minStck;
public:
	MinStack1() {
	}

	void push(int val) {
		stck.push(val);
		if (minStck.empty() || val <= minStck.top())
			minStck.push(val);
	}

	void pop() {
		int x = stck.top();
		stck.pop();
		if (!minStck.empty() && x == minStck.top())
			minStck.pop();
	}

	int top() {
		return stck.top();
	}

	int getMin() {
		return minStck.top();
	}
};

// T.C - O(N) S.C. - O(N)
//Uses 1 Stack - Consider each node in the stack having a minimum value.
class MinStack2 {
	// stack <val, min_val>
	stack<pair<int, int>> stack;
public:
	MinStack2() {

	}

	void push(int val) {
		if(stack.empty())
			stack.push({ val, val });
		else {
			int min = stack.top().second;
			if (val <= min)
				stack.push({ val, val });
			else
				stack.push({ val, min });
		}
	}

	void pop() {
		stack.pop();
	}

	int top() {
		return stack.top().first;
	}

	int getMin() {
		return stack.top().second;
	}
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main() {
	MinStack1 minStack1;
	minStack1.push(-2);
	minStack1.push(0);
	minStack1.push(-3);
	cout << minStack1.getMin() << endl; // return -3
	minStack1.pop();
	cout << minStack1.top() << endl;    // return 0
	cout << minStack1.getMin() << endl; // return -2


	MinStack1 minStack2;
	minStack2.push(-2);
	minStack2.push(0);
	minStack2.push(-3);
	cout << minStack2.getMin() << endl; // return -3
	minStack2.pop();
	cout << minStack2.top() << endl;    // return 0
	cout << minStack2.getMin() << endl; // return -2
	return 0;
}