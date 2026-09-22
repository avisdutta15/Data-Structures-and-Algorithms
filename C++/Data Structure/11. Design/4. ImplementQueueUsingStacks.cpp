#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 232 - Implement Queue using Stacks

    Implement a FIFO queue using only two stacks. The queue should
    support: push, pop, peek, and empty.

    Implement the MyQueue class:
        - void push(int x):  pushes x to the back of the queue.
        - int pop():         removes and returns the front element.
        - int peek():        returns the front element without removing.
        - bool empty():      returns true if the queue is empty.

    Examples:
    ---------

    Example 1:
        MyQueue q;
        q.push(1);     // queue: [1]
        q.push(2);     // queue: [1, 2]
        q.peek();      // returns 1 (front)
        q.pop();       // returns 1. queue: [2]
        q.empty();     // false

    Constraints:
    ------------
    - 1 <= x <= 9
    - At most 100 calls to push, pop, peek, empty.
    - All calls to pop and peek are valid (queue is non-empty).

    Approach: Two Stacks (Lazy Transfer)
    --------------------------------------
    Stacks are LIFO, queues are FIFO. If you push 1, 2, 3 onto a
    stack, popping gives 3, 2, 1 (reversed). But if you pop all into
    a SECOND stack, the second stack has 1, 2, 3 on top — FIFO order.

    input stack:  receives all pushes (back of queue).
    output stack: serves all pops/peeks (front of queue).

    The trick: only transfer from input → output when output is EMPTY.
    This is the "lazy transfer" — we don't move elements on every
    operation, only when needed.

    Why lazy? Each element is moved at most once (input → output).
    So n operations cost O(n) total = O(1) amortized per operation.

    Why not transfer on every push?
    --------------------------------
    That would be the "expensive push" approach:
        push: move all from input→output, push x, move all back. O(n).
        pop:  O(1).

    This gives O(n) per push = O(n²) for n pushes.
    Lazy transfer gives O(1) amortized — strictly better.

    Dry Run:
    --------
    push(1):  input: [1]       output: []
    push(2):  input: [1, 2]    output: []
    peek():   output is empty → transfer: input→output.
              input: []        output: [2, 1]  (1 on top = front)
              returns 1 ✓
    pop():    output: [2, 1]. Pop top = 1. output: [2].
              returns 1 ✓
    push(3):  input: [3]       output: [2]
    pop():    output not empty. Pop top = 2.
              output: []       input: [3]
              returns 2 ✓
    pop():    output empty → transfer. output: [3]. Pop = 3.
              returns 3 ✓

    Complexity Analysis:
    --------------------
    push:    O(1)
    pop:     O(1) amortized (O(n) worst case when transferring)
    peek:    O(1) amortized
    empty:   O(1)
    Space:   O(n) — two stacks hold all n elements total.

*/

class MyQueue {
private:
    stack<int> input, output;
public:
    MyQueue() {

    }

    void push(int x) {
        input.push(x);
    }

    int pop() {
        if(empty()) return -1;

        if(output.empty()){
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
        }
        int top = output.top();
        output.pop();
        return top;
    }

    int peek() {
        if(empty()) return -1;

        if(output.empty()){
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
        }
        int top = output.top();
        return top;
    }

    bool empty() {
        return input.empty() && output.empty();
    }
};


int main() {
    // LeetCode example
    MyQueue q;
    q.push(1);
    q.push(2);
    cout << q.peek() << endl;     // 1
    cout << q.pop() << endl;      // 1
    cout << q.empty() << endl;    // 0 (false)

    // Additional: interleaved push and pop
    MyQueue q2;
    q2.push(10);
    q2.push(20);
    q2.push(30);
    cout << q2.pop() << endl;     // 10 (FIFO: first in, first out)
    q2.push(40);
    cout << q2.pop() << endl;     // 20
    cout << q2.pop() << endl;     // 30
    cout << q2.pop() << endl;     // 40
    cout << q2.empty() << endl;   // 1 (true)

    return 0;
}