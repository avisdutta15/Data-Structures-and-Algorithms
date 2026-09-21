#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

/*
    https://www.youtube.com/shorts/6Q0JCbUtJZk
    
    Problem Statement:
    ------------------
    LeetCode 155 - Min Stack

    Design a stack that supports push, pop, top, and retrieving the
    minimum element, all in O(1) time.

    Implement the MinStack class:
        - MinStack():       initializes the stack.
        - void push(val):   pushes val onto the stack.
        - void pop():       removes the top element.
        - int top():        returns the top element.
        - int getMin():     returns the minimum element in the stack.

    Examples:
    ---------

    Example 1:
        MinStack s;
        s.push(-2);    // stack: [-2],       min: -2
        s.push(0);     // stack: [-2, 0],    min: -2
        s.push(-3);    // stack: [-2, 0, -3], min: -3
        s.getMin();    // returns -3
        s.pop();       // stack: [-2, 0],     min: -2
        s.top();       // returns 0
        s.getMin();    // returns -2

    Constraints:
    ------------
    - -2^31 <= val <= 2^31 - 1
    - pop, top, and getMin are always called on non-empty stacks.
    - At most 3 * 10^4 calls total.

    Approach: Two Stacks
    ---------------------
    Use a main stack for normal operations and a second "min stack"
    that tracks the current minimum.

    _stack:     holds all elements (normal stack behavior).
    _min_stack: holds minimums. Its top is always the current min.

    How _min_stack works:
        push(val): push onto _min_stack ONLY if val <= _min_stack.top().
            This means _min_stack only grows when we see a new (or equal)
            minimum.

        pop(): if the popped value == _min_stack.top(), pop _min_stack too.
            The minimum is being removed, so the previous minimum
            (below it in _min_stack) takes over.

    Why <= and not < ?
        Handles duplicates. If we push 1, 1:
            With <=: _min_stack = [1, 1]. Pop one 1 → _min_stack = [1]. Correct.
            With <:  _min_stack = [1].    Pop one 1 → _min_stack = []. Wrong!
                     There's still a 1 in _stack, but _min_stack is empty.

    Dry Run:
    --------
        push(-2):  _stack: [-2]          _min_stack: [-2]
        push(0):   _stack: [-2, 0]       _min_stack: [-2]       (0 > -2, skip)
        push(-3):  _stack: [-2, 0, -3]   _min_stack: [-2, -3]   (-3 <= -2, push)
        getMin():  _min_stack.top() = -3 ✓
        pop():     popped -3. -3 == _min_stack.top() → pop _min_stack too.
                   _stack: [-2, 0]       _min_stack: [-2]
        top():     _stack.top() = 0 ✓
        getMin():  _min_stack.top() = -2 ✓

    Complexity Analysis:
    --------------------
    push:    O(1)
    pop:     O(1)
    top:     O(1)
    getMin:  O(1)
    Space:   O(n) — worst case both stacks hold all n elements
                     (when values are pushed in descending order).

*/

class MinStack {
private:
    stack<int> _stack;
    stack<int> _min_stack;
public:
    MinStack() {

    }

    void push(int value) {
        _stack.push(value);
        if(_min_stack.empty() || value <= _min_stack.top())
            _min_stack.push(value);
    }

    void pop() {
        int poppedValue = _stack.top();
        _stack.pop();
        if (_min_stack.top() == poppedValue)
            _min_stack.pop();
    }

    int top() {
        return _stack.top();
    }

    int getMin() {
        return _min_stack.top();
    }
};

int main() {
    MinStack s;

    // LeetCode example
    s.push(-2);
    s.push(0);
    s.push(-3);
    cout << s.getMin() << endl;   // -3
    s.pop();
    cout << s.top() << endl;      // 0
    cout << s.getMin() << endl;   // -2

    // Duplicate min test
    MinStack s2;
    s2.push(1);
    s2.push(1);
    cout << s2.getMin() << endl;  // 1
    s2.pop();
    cout << s2.getMin() << endl;  // 1 (still correct with <=)

    // Descending order (worst case for space)
    MinStack s3;
    s3.push(3);
    s3.push(2);
    s3.push(1);
    cout << s3.getMin() << endl;  // 1
    s3.pop();
    cout << s3.getMin() << endl;  // 2
    s3.pop();
    cout << s3.getMin() << endl;  // 3

    return 0;
}