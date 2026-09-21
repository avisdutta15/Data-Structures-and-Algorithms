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
    Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.

    Examples:
    --------
    Input: s = "(()"
    Output: 2
    Explanation: The longest valid parentheses substring is "()".

    Input: s = ")()())"
    Output: 4
    Explanation: The longest valid parentheses substring is "()()".

    Input: s = ""
    Output: 0

    Approach 2: T.C.- O(N) S.C. - O(N)
    ----------------------------------
    Core Strategy
    To find the length of a valid substring, you need to know where it ends and where it started. 
    By storing the indices of the characters in the stack, we can calculate the length of any valid 
    sequence on the fly by doing simple math: [Current Index - Starting Boundary Index.]


    2. The Magic of the Initial -1 (The Anchor)
    Before the loop starts, the code does stack.push(-1). This is the secret sauce of the algorithm.
    The -1 acts as an anchor or a boundary for the last invalid character. 
    It represents a hypothetical invalid ) right before the start of the string. 
    This way, if the very first valid pair is at index 0 and 1 (), the math evaluates to 1 - (-1) = 2, which is exactly correct!

    3. The Rules of the Loop
    As you iterate through the string, the algorithm follows two simple rules depending on the character:
    
        Rule A: If you see an opening bracket (
            You simply push its index onto the stack. This index is waiting to be matched with a future ).
        Rule B: If you see a closing bracket )
            You immediately pop() the top of the stack. This pops the index of the matching '('.
            Condition 1 (The stack is now empty): This means the ) you just processed did not have a matching (. 
                                                  It is an invalid bracket! Because it breaks the valid sequence, 
                                                  we push its current index i onto the stack. This index becomes 
                                                  the new anchor/boundary for any valid sequences that might come 
                                                  after it.

            Condition 2 (The stack is not empty): We found a valid match! The length of this valid sequence is 
                                                  calculated by subtracting the current index i from whatever index is 
                                                  currently sitting at the top of the stack (which is our anchor). 
                                                  We then update maxLen if this new length is bigger.

    Approach 3: T.C.- O(N+N) S.C. - O(1)
    ----------------------------------
    Instead of storing indices in a stack, the algorithm just uses two counters (opening and closing).
    As it reads the string:
        1. If opening == closing, we have a perfectly balanced valid substring! We calculate its length.
        2. If closing > opening, the sequence is broken (e.g., ())). We reset both counters to 0 and start 
        fresh from the next character.

    Why are 2 traversals required?
        The first traversal (Left-to-Right) has a blind spot: 
        it only resets when there is a surplus of closing brackets ). 
        It fails to register valid substrings if there is an unresolved surplus of opening brackets (.

        The Failing Example: s = "(()"
        If we only go Left-to-Right:
            Read ( -> opening = 1, closing = 0
            Read ( -> opening = 2, closing = 0
            Read ) -> opening = 2, closing = 1
            Result: Because opening (2) never equals closing (1), maxLen stays at 0. 
            
        We completely missed the valid () at the end!
        
        The Fix (Right-to-Left Pass):By doing a second pass from back to front, we reverse the logic.
        If we read (() from Right-to-Left:
            Read ) -> closing = 1, opening = 0
            Read ( -> closing = 1, opening = 1 -> MATCH! maxLen = 2
            Read ( -> opening = 2, closing = 1 -> Reset!
*/


// Brute Force
class Solution1 {
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
    bool isValid(string s, int i, int j) {
        stack<char> stack;

        for(int idx = i; idx <=j; idx++){
            char c = s[idx];
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

public:
    int longestValidParentheses(string s) {
        int maxLength = 0;

        for (int i = 0; i < s.length(); i++) {
            for (int j = i + 1; j < s.length(); j++) {
                if(isValid(s, i, j)){
                    int len = j - i + 1;
                    maxLength = max(maxLength, len);
                }
            }
        }
        return maxLength;
    }
};


// Using Stack
class Solution2 {
public:
    int longestValidParentheses(string s) {
        if (s.length() == 0)
            return 0;

        int maxLen = 0;
        stack<int> stack;
        stack.push(-1);

        for (int i = 0; i < s.length(); i++) {
            // push index for an opening bracket
            if (s[i] == '(') {
                stack.push(i);
            } else {
                // pop the 
                stack.pop();
                if (stack.empty())
                    stack.push(i);
                else {
                    int len = i - stack.top();
                    maxLen = max(maxLen, len);
                }
            }
        }

        return maxLen;
    }
};

class Solution3{
public:
    int longestValidParentheses(string s) {
        int maxLen = 0;
        int opening = 0, closing = 0;

        for(int i=0; i<s.length(); i++){
            if(s[i] == '(')
                opening++;
            else{
                closing++;
                // if we found a valid substring. Then measue length
                if(opening == closing){
                    maxLen = max(maxLen, opening + closing);
                }
                else if(closing > opening){
                    opening = 0, closing = 0;
                }
            }
        }

        // "(()" -> This would not have created any valid substring in 1st pass.
        // So we need a 2nd pass from back to front with inverse criteria.

        opening = 0, closing = 0;
        for(int i=s.length()-1; i>=0; i--){
            if(s[i] == ')')
                closing++;
            else{
                opening++;
                // if we found a valid substring. Then measue length
                if(opening == closing){
                    maxLen = max(maxLen, opening + closing);
                }
                else if(opening > closing){
                    opening = 0, closing = 0;
                }
            }
        }
        return maxLen;
    }
};

int main(){
    Solution1 obj1;
    cout<<obj1.longestValidParentheses("(()())")<<endl;

    return 0;
}