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
    Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
    determine if the input string is valid.
    
    An input string is valid if:
    
    - Open brackets must be closed by the same type of brackets.
    - Open brackets must be closed in the correct order.
    - Every close bracket has a corresponding open bracket of the same type.

    Examples:
    --------- 
    Input: s = "()"
    Output: true

    Input: s = "()[]{}"
    Output: true

    Input: s = "(]"
    Output: false

    Input: s = "([])"
    Output: true

    Input: s = "([)]"
    Output: false

    Constraints:
    ------------
    1 <= s.length <= 104
    s consists of parentheses only '()[]{}'.


    Approach: 
    ---------
    Stack to validate the string
*/

class Solution {
private:
    bool isOpening(char c){
        return c=='(' || c=='[' || c=='{';
    }

    bool isClosing(char c){
        return c==')' || c==']' || c=='}';
    }

    bool isMatching(char opening, char closing){
        return (opening=='(' && closing == ')')
            || (opening=='{' && closing == '}')
            || (opening=='[' && closing == ']');
    }
public:
    bool isValid(string s) {
        stack<char> stack;

        for(char c : s){
            if(isOpening(c)){
                stack.push(c);
            }
            else if(isClosing(c)){
                if(stack.empty())
                    return false;
                if(!isMatching(stack.top(), c))
                    return false;
                stack.pop();
            }
        }

        if(!stack.empty())
            return false;
        return true;
    }
};

int main(){
    Solution obj;
    cout<<obj.isValid("()()")<<endl;
    cout<<obj.isValid("[(])]")<<endl;

    return 0;
}