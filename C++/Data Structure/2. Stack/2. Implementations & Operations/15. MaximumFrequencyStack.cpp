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
	https://www.youtube.com/watch?v=KVg4Y0sI4Iw
	Problem Statement:
	-----------------
	Design a stack-like data structure to push elements to the stack and 
    pop the most frequent element from the stack.
    
    Implement the FreqStack class:
        - FreqStack() constructs an empty frequency stack.
        - void push(int val) pushes an integer val onto the top of the stack.
        - int pop() removes and returns the most frequent element in the stack. 
            - If there is a tie for the most frequent element, the element closest 
              to the stack's top is removed and returned.
	 
	Examples:
	---------
	Input
    ["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
    [[], [5], [7], [5], [7], [4], [5], [], [], [], []]
    Output
    [null, null, null, null, null, null, null, 5, 7, 5, 4]

    Explanation
    FreqStack freqStack = new FreqStack();
    freqStack.push(5); // The stack is [5]
    freqStack.push(7); // The stack is [5,7]
    freqStack.push(5); // The stack is [5,7,5]
    freqStack.push(7); // The stack is [5,7,5,7]
    freqStack.push(4); // The stack is [5,7,5,7,4]
    freqStack.push(5); // The stack is [5,7,5,7,4,5]
    freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
    freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. 
                       // The stack becomes [5,7,5,4].
    freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
    freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. 
                       // The stack becomes [5,7].

	Constraints:
	------------
	It is guaranteed that there will be at least one element in the stack before calling pop.


	Approach:
	--------
    unordered_map <int, int> val_frequency_map
    unordered_map <int, stack<int>> freq_stack_map
    
    push(5) : val_frequency_map[5] = 1, freq_stack_map[1].push(5), max_freq = 1
    push(7) : val_frequency_map[7] = 1, freq_stack_map[1].push(7), max_freq = max(1, 1) = 1
    push(5) : val_frequency_map[5] = 2, freq_stack_map[2].push(5), max_freq = max(1, 2) = 2
    push(7) : val_frequency_map[7] = 2, freq_stack_map[2].push(7), max_freq = max(2, 2) = 2
    push(4) : val_frequency_map[4] = 1, freq_stack_map[1].push(4), max_freq = max(2, 1) = 2
    push(5) : val_frequency_map[5] = 3, freq_stack_map[3].push(5), max_freq = max(2, 3) = 3
    pop()   : return freq_stack_map[3].top() = 5, pop() -> 5
    pop()   : return freq_stack_map[2].top() = 7, pop() -> 7
    pop()   : return freq_stack_map[2].top() = 5, pop() -> 5
    push(5) : val_frequency_map[5] = 4, freq_stack_map[4].push(5), max_freq = max(3, 4) = 4

    Time Complexity: O(1) 
    Space Complexity: O(N)        
*/


class FreqStack {
private:
    // map to store the frequency of each item
    unordered_map<int, int> val_freq_map;

    // map to store the freq and its corresponding stack
    unordered_map<int, stack<int>> freq_stack_map;

    int max_freq;
public:
    FreqStack() {
        max_freq = 0;
    }

    void push(int val) {
        // insert the value and increase its frequency
        val_freq_map[val]++;

        // insert the item into the stack of the corresponsing frequency
        int freq = val_freq_map[val];
        freq_stack_map[freq].push(val);

        // update the max_freq
        max_freq = max(max_freq, freq);
    }

    int pop() {
        // get the top item of the max_freq stack and pop it
        int item = freq_stack_map[max_freq].top();
        freq_stack_map[max_freq].pop();

        // decrement its frequency
        val_freq_map[item]--;

        // if the max_freq stack becomes empty 
        // then update the max_freq. i.e. max_freq = max_freq-1
        if (freq_stack_map[max_freq].empty())
            max_freq--;

        // return the top item
        return item;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */

int main() {
    FreqStack obj;
    obj.push(12);
    obj.push(12);

	return 0;
}