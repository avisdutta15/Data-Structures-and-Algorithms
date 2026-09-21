#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
    Problem Statement:
    -----------------
    Design a stack data structure that supports the following four operations, each in constant time complexity, i.e., O(1):
        push(x): Insert an element x onto the top of the stack.
        pop(): Remove and return the element at the top of the stack.
        findMiddle(): Retrieve the middle element of the stack without removing it.
        deleteMiddle(): Remove the middle element from the stack.

    Examples:
    --------- 
    Input: operations =["push", "push", "findMiddle", "pop", "deleteMiddle"]
    values = [[1], [2], [], [], []]
    Output: 2 1
    Explanation: Let's break down the sequence of operations more clearly:

        First Operation: Push the value 1 onto the stack.
        Second Operation: Push the value 2 onto the stack. At this point, the stack (from bottom to top) is: [1, 2].
        Third Operation: Retrieve the middle element. Since the stack contains two items, the middle element 
                         is defined as 2 (second middle).
        Fourth Operation: Pop the top element, which is 2, removing it from the stack.
        Fifth Operation: Delete the middle element. With 2 already removed, only 1 remains; hence, 
                         1 is also deleted.

    Constraints:
    ------------
   


    Approach 1: 
    ------------
    Doubly Linked List based implementation + Middle Node Tracking

    1. Push -> If the size of the stack becomes even, update the mid to mid->next;
    2. Pop -> If the size of the stack becomes odd, update the mid to mid->prev;
    3. findMiddle() -> Return the data at the middle node.
    4. deleteMiddle() -> Delete the middle node and update the middle pointer accordingly.
                         After delete if the size of the list becomes:
                         odd : new middle = middle->prev
                         even: new middle = middle->next
    For all the above, size = 0, 1 are special case. So handle accordingly.

    Time Complexity: O(1)
    Space Complexity: O(N)
    
*/

struct Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int data, Node* next, Node* prev)
        : data(data), next(next), prev(prev){}
};

class MiddleStack {
private:
    Node* head;
    Node* tail;
    Node* middle;
    int size;
public:
    MiddleStack() {
        head = nullptr;
        tail = head;
        middle = head;
        size = 0;
    }

    // On Push. If the size of the stack becomes even, update the mid to mid->next;
    // size = 1 special case.
    // m
    // 1  
    //    m
    // 1->2
    //    m
    // 1->2->3
    //       m
    // 1->2->3->4
    void push(int x) {
        Node* newNode = new Node(x, nullptr, nullptr);

        // size = 1 special case.
        if (head == nullptr) {
            head = newNode;
            middle = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }            
        
        size++;

        if(size % 2 ==0)
            middle = middle->next;
    }

    // On Pop. If the size of the stack becomes odd, update the mid to mid->prev;
    // size = 1, 0 special case.
    //       m
    // 1->2->3->4
    //    m
    // 1->2->3
    //    m
    // 1->2    
    // m
    // 1
    int pop() {
        if (head == nullptr)
            return -1;

        // collect data
        int data = tail->data;

        // detach tail
        Node* tempNode = tail;
        tempNode->next = nullptr;
        tail = tail->prev;

        // delete tail
        delete tempNode;
        tempNode = nullptr;
        
        size--;

        if (size == 0) {
            head = nullptr;
            tail = head;
            middle = head;

            return data;
        }

        // If size becomes odd, move middle to previous node
        if (size % 2 != 0 && size != 1)
            middle = middle->prev;
        // special case if size = 1
        else if (size == 1)
            middle = head;

        return data;
    }

    int top() {
        if (head == nullptr)
            return -1;
        return tail->data;
    }

    int getMiddle() {
        if (head == nullptr)
            return -1;
        return middle->data;
    }
    
    // On deleting the middle node, if the size of the list becomes
    // odd : new middle = middle->prev
    // even : new middle = middle->next
    // size = 0 special case.
    //       m
    // 1->2->3->4
    //    m
    // 1->2->4
    //    m
    // 1->4
    // m
    // 1
    void deleteMiddle() {
        if (head == nullptr)
            return;
        
        if (size > 1) {
            size--;
            if (size % 2 != 0) {
                Node* middlePrev = middle->prev;
                middlePrev->next = middle->next;
                delete middle;
                middle = middlePrev;
            }
            else if (size % 2 == 0) {
                Node* middleNext = middle->next;
                middleNext->prev = middle->prev;
                delete middle;
                middle = middleNext;
            }
        }
        else {
            head = nullptr;
            tail = head;
            middle = head;
            size--;
        }
    }
};

int main() {
    MiddleStack stack;
    stack.push(1);
    cout << "Stack: [1]" << endl;
    cout<<stack.getMiddle()<<endl;
    stack.push(2);
    cout << "Stack: [1 2]" << endl;
    cout<<stack.getMiddle()<<endl;
    stack.push(3);
    cout << "Stack: [1 2 3]" << endl;
    cout << stack.getMiddle() << endl;
    stack.push(4);
    cout << "Stack: [1 2 3 4]" << endl;
    cout << stack.getMiddle() << endl;
    stack.push(5);
    cout << "Stack: [1 2 3 4 5]" << endl;
    cout << stack.getMiddle() << endl;
    stack.push(6);
    cout << "Stack: [1 2 3 4 5 6]" << endl;
    cout << stack.getMiddle() << endl;


    stack.deleteMiddle();
    cout << "Stack: [1 2 3 5 6]" << endl;
    cout << stack.getMiddle() << endl;
    stack.deleteMiddle();
    cout << "Stack: [1 2 5 6]" << endl;
    cout << stack.getMiddle() << endl;
    stack.deleteMiddle();
    cout << "Stack: [1 2 6]" << endl;
    cout << stack.getMiddle() << endl;
    stack.deleteMiddle();
    cout << "Stack: [1 6]" << endl;
    cout << stack.getMiddle() << endl;
    stack.deleteMiddle();
    cout << "Stack: [1]" << endl;
    cout << stack.getMiddle() << endl;
    stack.deleteMiddle();
    cout << "Stack: []" << endl;
    cout << stack.getMiddle() << endl;


    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);

    stack.pop();
    cout << "Stack: [1 2 3 4 5]" << endl;
    cout << stack.getMiddle() << endl;

    stack.pop();
    cout << "Stack: [1 2 3 4]" << endl;
    cout << stack.getMiddle() << endl;

    stack.pop();
    cout << "Stack: [1 2 3]" << endl;
    cout << stack.getMiddle() << endl;

    stack.pop();
    cout << "Stack: [1 2]" << endl;
    cout << stack.getMiddle() << endl;

    stack.pop();
    cout << "Stack: [1]" << endl;
    cout << stack.getMiddle() << endl;

    stack.pop();
    cout << "Stack: []" << endl;
    cout << stack.getMiddle() << endl;

    return 0;
}