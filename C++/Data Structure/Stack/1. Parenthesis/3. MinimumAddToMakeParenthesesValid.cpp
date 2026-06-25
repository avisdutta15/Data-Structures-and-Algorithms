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
    ------------------
    Minimum Add to Make Parentheses Valid
    A parentheses string is valid if and only if:
    - It is the empty string,
    - It can be written as AB (A concatenated with B), where A and B are valid strings, or 
    - It can be written as (A), where A is a valid string.
    
    You are given a parentheses string s. In one move, you can insert a parenthesis at 
    any position of the string.
    
    For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or 
    a closing parenthesis to be "())))".
    
    Return the minimum number of moves required to make s valid.
    
    Examples:
    ---------
    Input: s = "())"
    Output: 1

    Input: s = "((("
    Output: 3

    Approach:
    ---------
    In Stack we store the invalid brackets.
    Whenever we find a valid pair, we pop from stack.
    At the end the stack has invalid brackets for whome we need the corresponding partner.

    Traverse 0 to n-1:
        if (
            push (
        else if )
            if !stack.empty() and stack.top == (  //valid pair found
                stack.pop();
            else
                stack.push )

    return stack.size;
*/

class Solution1 {
public:
    int minAddToMakeValid(string S) {
        stack<char> stack;
        
        for(char c: S){
            // if opening bracket then push to stack
            if(c == '(')
                stack.push(c);
            // if closing bracket then
            else if(c == ')'){
                // if we have opening bracket then pop it and continue.
                // This means its a valid
                if(!stack.empty() && stack.top()=='(')
                    stack.pop();
                else
                // else store the ) bracket as we need a ( bracket for it.
                    stack.push(c);
            }
        }
        
        // return the length of the stack.
        // the stack has ( brackets that has no ) brackets.
        // the stack has ) bracket that has no ( brackets.
        return stack.size();
    }
};

class Solution2 {
public:
    int minAddToMakeValid(string S) {
        int opening = 0, closing = 0;

        for(char c: S){
            // if opening bracket then push to stack (opening++)
            if(c == '(')
                opening++;
            // if closing bracket then
            else if(c == ')'){
                // if we have opening bracket then pop it and continue. (opening--)
                // This means its a valid
                if(opening > 0)
                    opening--;
                else
                // else store the ) bracket as we need a ( bracket for it. (closing++)
                    closing++;
            }
        }
        
        // return the length of the stack.
        // the stack has ( brackets that has no ) brackets.
        // the stack has ) bracket that has no ( brackets.
        return opening + closing;
    }
};


int main(){
    return 0;
}