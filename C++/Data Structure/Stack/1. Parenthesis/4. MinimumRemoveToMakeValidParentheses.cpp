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
	https://www.youtube.com/watch?v=NNxaYz0nrk0
	Problem Statement:
	-----------------
	Given a string s of '(' , ')' and lowercase English characters.

    Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) 
    so that the resulting parentheses string is valid and return any valid string.
    
    Formally, a parentheses string is valid if and only if:
        - It is the empty string, contains only lowercase characters, or
        - It can be written as AB (A concatenated with B), where A and B are valid strings, or
        - It can be written as (A), where A is a valid string.
	 
	Examples:
	---------
	Input: s = "lee(t(c)o)de)"
    Output: "lee(t(c)o)de"
    Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

    Input: s = "a)b(c)d"
    Output: "ab(c)d"

    Input: s = "))(("
    Output: ""
    Explanation: An empty string is also valid.

	Constraints:
	------------
	1 <= s.length <= 10^5
    s[i] is either '(' , ')', or lowercase English letter.

	Approach:
	--------
    Find out all the invalid parenthesis. i.e. parenthesis without matching pair.
    These parenthesis needs to be removed from the string.
    So we mark these invalid parenthesis in the string with a marker e.g. '*'
    and finally build the result string by skipping these marked characters.

    Using Stack - store indices of invalid parenthesis
    ---------------------------------------------------
    Push char index into the stack when we see '('.
    Pop from the stack when we see ')'.
        If the stack is empty, then we have ')' without the pair, and it needs to be removed.
    In the end, the stack will contain indexes of '(' without the pair, if any. 
    We need to remove all of them too.

        First pass - mark all invalid ')' with *
        Second pass - mark all invalid '(' with *

    Now create a result string by skipping '*' marked characters.

    Time Complexity: O(n)
    Space Complexity: O(n)

    Without using stack
    --------------------
    We will identify invalid '(' and ')' using 1 variable - opening
    
    First pass - mark all invalid ) with *
        if (
            opening++
        else if )
            if(opening == 0)
                this ) is inavalid
                mark s[i] = *
            else if (opening > 0)
                opening--
	    
    Second pass - mark all invalid ( with *
        i = n-1 to 0
            if s[i] ( and opening > 0 that 
                mark s[i] = *
            else if opening == 0
                break;

    Now create a result string by skipping '*' marked characters.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

// Using Stack
class Solution1 {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> stack;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == '(')
                stack.push(i);
            else if (c == ')') {
                if (!stack.empty() && s[stack.top()] == '(')
                    stack.pop();
                else // this is an invalid ) so mark it in string
                    s[i] = '*';
            }
        }

        // mark the invalid ( in string
        while (!stack.empty()) {
            s[stack.top()] = '*';
            stack.pop();
        }

        string result = "";
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != '*')   //skip marked 
                result.push_back(s[i]);
        }
        return result;
    }
};

// Without using Stack. Use only 1 variable - opening
class Solution2 {
public:
    string minRemoveToMakeValid(string s) {
        int opening = 0;
        int closing = 0;

        // First pass: mark all invalid ')'
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
                opening++;
            else if (s[i] == ')') {
                if (opening == 0)
                    s[i] = '*'; //Mark excessive )
                else
                    opening--;
            }
        }

        // Second Pass: mark all invalid '('
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (opening > 0 && s[i] == '(')
            {
                s[i] = '*';
                opening--;
            }
        }

        // Now all the extra ( and ) in the input string have been marked with *
        string res = "";
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '*')
                continue;
            else
                res.push_back(s[i]);
        }

        return res;

        /*
        // We can also do the same without the res string
        int end = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '*')
                continue;
            else
                s[end++] = s[i];
        }

        return s.substr(0, end);
        */
    }
};

int main() {
	Solution1 obj;
	cout << obj.minRemoveToMakeValid("lee(t(c)o)de)") << endl;
    cout << obj.minRemoveToMakeValid("a)b(c)d") << endl;

	return 0;
}