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
	https://www.youtube.com/watch?v=Pno2hATcwHA
	Problem Statement:
	-----------------
	Given a string s containing only three types of characters: '(', ')' and '*', 
    return true if s is valid.

    The following rules define a valid string:
        -   Any left parenthesis '(' must have a corresponding right parenthesis ')'.
        -   Any right parenthesis ')' must have a corresponding left parenthesis '('.
        -   Left parenthesis '(' must go before the corresponding right parenthesis ')'.
        -   '*' could be treated as a single right parenthesis ')' or a single left 
            parenthesis '(' or an empty string "".
	 
	Examples:
	---------
	Input: s = "()"
    Output: true

    Input: s = "(*)"
    Output: true

    Input: s = "(*))"
    Output: true

	Constraints:
	------------
	1 <= s.length <= 100
    s[i] is '(', ')' or '*'.

	Approach:
	--------
    1. We keep two stacks, one for open brackets and another for asterisks.

    2. The first stack keeps track of the indices of encountered open brackets, 
    while the second stack is dedicated to storing the indices of asterisks.
    
    3. As we traverse through the input string, every time we encounter an open 
    bracket or an asterisk, we record its index by pushing it onto the respective stack.
    
    4. When we encounter a right bracket, we first attempt to balance this right 
    bracket with an open bracket. To do so, we peek into our open bracket stack. 
    If it's not empty, indicating that there's a matching open bracket available, 
    we pop the index from this stack and proceed.
    
    5. However, if the open bracket stack is empty, we resort to using an asterisk. 
    In this scenario, we peek into our asterisk stack and check if it contains any 
    available asterisks. If so, we pop the index from this stack and proceed. 
    This dynamic selection process ensures that we exhaust all possible options for 
    balancing the right bracket.
    
    6. If both the open bracket and asterisk stacks are empty, we return false, 
    as this indicates an unmatched right bracket.
    
    7. Once we've processed the whole string, our attention shifts to the remaining 
    elements in the open bracket and asterisk stacks. Here, we check their positions 
    relative to each other. We recognize that if an open bracket appears after the 
    last encountered asterisk, there's no viable way to balance it because we have no 
    available right brackets. Therefore, we return false. However, if no such mismatch 
    is detected, we proceed to empty both stacks.

    8. Here we used a greedy strategy, prioritizing the use of open brackets over asterisks 
    whenever possible to balance the right brackets. This ensures that we exhaust all available 
    options for balancing before resorting to using asterisks.

    Time Complexity: O(n)
    Space Complexity: O(n)
	
*/

class Solution {
public:
    bool checkValidString(string s) {
        stack<int> parenStack;
        stack<int> asterikStack;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(')
                parenStack.push(i);
            else if (s[i] == '*')
                asterikStack.push(i);
            else if (s[i] == ')') {
                // lets try to balance this ')'
                if (!parenStack.empty() && s[parenStack.top()] == '(')
                    parenStack.pop();
                else if (!asterikStack.empty())
                    asterikStack.pop();
                else
                    //there is no way to balance the )
                    return false;
            }
        }

        // Now lets balance the ( 
        while (!parenStack.empty() && !asterikStack.empty()) {
            // in order to balance the (,  * should be present so that 
            // it can be converted (hypothetically) to ), 
            // also the * should come after (
            if (parenStack.top() < asterikStack.top()) {
                parenStack.pop();
                asterikStack.pop();
            }
            else
                return false;
        }

        // at last we should not have any ().
        // it doesnot matter if we have * left as * can be translated to "" in that case
        return parenStack.empty();
    }
};

int main() {
	Solution obj;
	cout << obj.checkValidString("(*)") << endl;
    cout << obj.checkValidString("(*))") << endl;

	return 0;
}