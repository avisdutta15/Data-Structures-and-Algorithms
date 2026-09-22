#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 225 - Implement Stack using Queues

    Implement a LIFO stack using only queues. The stack should
    support: push, pop, top, and empty.

    Implement the MyStack class:
        - void push(int x):  pushes x to the top of the stack.
        - int pop():         removes and returns the top element.
        - int top():         returns the top element without removing.
        - bool empty():      returns true if the stack is empty.

    Examples:
    ---------

    Example 1:
        MyStack s;
        s.push(1);     // stack: [1]
        s.push(2);     // stack: [1, 2]  (2 is on top)
        s.top();       // returns 2
        s.pop();       // returns 2. stack: [1]
        s.empty();     // false

    Constraints:
    ------------
    - 1 <= x <= 9
    - At most 100 calls to push, pop, top, empty.
    - All calls to pop and top are valid (stack is non-empty).

    Approach: Single Queue with Rotation
    --------------------------------------
    A queue is FIFO (oldest first), but a stack needs LIFO (newest
    first). After pushing x, rotate the queue so x moves to the front.

    push(x):
        1. Push x to back of queue.
        2. Rotate: pop from front and push to back, (size-1) times.
           This moves all older elements behind x.
           Now x is at the front = top of stack.

    pop/top: just access the front — it's always the newest element.

    Why does rotation work?
    -----------------------
    Before push(3): Q = [2, 1]   (2 is the current "top")

    Step 1: Q.push(3)    → Q = [2, 1, 3]
    Step 2: Rotate size-1 = 2 times:
        Move 2 to back:  Q = [1, 3, 2]
        Move 1 to back:  Q = [3, 2, 1]

    Now 3 (newest) is at the front. LIFO order maintained.

    Why not a lazy approach like Queue-using-Stacks?
    --------------------------------------------------
    In Queue-using-Stacks, reversing a stack into another stack
    gives FIFO order, and the reversal is amortized (each element
    moves once). Here, there's no equivalent trick — a queue always
    gives the oldest first. You MUST rearrange on every push to
    keep the newest at the front. O(n) push is unavoidable.

    Dry Run:
    --------
    push(1): Q = [1].       Rotate 0 times.   Q = [1]
    push(2): Q = [1, 2].    Rotate 1 time.    Q = [2, 1]
    push(3): Q = [2, 1, 3]. Rotate 2 times.   Q = [3, 2, 1]
    top():   Q.front() = 3 ✓
    pop():   Q.front() = 3, pop. Q = [2, 1]
    pop():   Q.front() = 2, pop. Q = [1]
    pop():   Q.front() = 1, pop. Q = []

    Complexity Analysis:
    --------------------
    push:    O(n) — rotate n-1 elements.
    pop:     O(1)
    top:     O(1)
    empty:   O(1)
    Space:   O(n) — single queue holds all elements.

*/

class MyStack {
private:
    queue<int> Q;

public:
    MyStack() {

    }

    void push(int x) {
        Q.push(x);
        
        // By moving all elements except the last one
        // from the front to the back of the queue (this.queue.length - 1 times),
        // it ensures that the last pushed element can be accessed first.
        int count = Q.size()-1;
        while(count > 0){
            Q.push(Q.front());
            Q.pop();
            count--;
        }
    }

    int pop() {
        int top = Q.front();
        Q.pop();
        return top;
    }

    int top() {
        int top = Q.front();
        return top;
    }

    bool empty() {
        return Q.empty();
    }
};



int main() {
    // LeetCode example
    MyStack s;
    s.push(1);
    s.push(2);
    cout << s.top() << endl;      // 2
    cout << s.pop() << endl;      // 2
    cout << s.empty() << endl;    // 0 (false)

    // LIFO order test
    MyStack s2;
    s2.push(10);
    s2.push(20);
    s2.push(30);
    cout << s2.pop() << endl;     // 30 (last in, first out)
    cout << s2.pop() << endl;     // 20
    cout << s2.top() << endl;     // 10
    cout << s2.pop() << endl;     // 10
    cout << s2.empty() << endl;   // 1 (true)

    return 0;
}