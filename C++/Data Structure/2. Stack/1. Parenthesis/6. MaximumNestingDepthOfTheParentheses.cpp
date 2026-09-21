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
    Given a valid parentheses string s, return the nesting depth of s. 
    The nesting depth is the maximum number of nested parentheses.

    Examples:
    ---------
    Input: s = "(1+(2*3)+((8)/4))+1"
    Output: 3
    Explanation: Digit 8 is inside of 3 nested parentheses in the string.

    Input: s = "(1)+((2))+(((3)))"
    Output: 3
    Explanation: Digit 3 is inside of 3 nested parentheses in the string.

    Approach:
    ---------
        level = 0
        for char i
            if s[i] == (    level++
            if s[i] == )    level--
            maxDepth = max(maxDepth, level);
*/


class Solution {
public:
    int maxDepth(string s) {
        int level = 0, maxLevel = 0;

        for(char c : s){
            if( c == '('){
                level++;
            }
            else if (c == ')')
                level--;
            maxLevel = max(maxLevel, level);
        }
        return maxLevel;
    }
};