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
	Given string num representing a non-negative integer num, and an integer k, 
    return the smallest possible integer after removing k digits from num.

	Examples:
	---------
	Input: num = "1432219", k = 3
    Output: "1219"
    Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

	Input: num = "10200", k = 1
    Output: "200"
    Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

    Input: num = "10", k = 2
    Output: "0"
    Explanation: Remove all the digits from the number and it is left with nothing which is 0.

    Constraints:
    -----------
    1 <= k <= num.length <= 105
    num consists of only digits.
    num does not have any leading zeros except for the zero itself.

	Approach:
	--------
	Use a stack to store digits of the resulting number
    Iterate through each digit of the input string
    While the stack is not empty, the current digit is smaller than the top of the stack, 
        and k is greater than 0, pop from the stack and decrement k
        
        Push the current digit onto the stack
    
    If k is still greater than 0 after the iteration, remove digits from the end of the stack
    Collect the remaining digits from the stack to form the result
    Remove any leading zeroes from the result
    If the result is empty after removing zeroes, return "0"

    Edge Cases:
    - If k is equal to the length of the input string, return "0" as all digits will be removed
    - If the result contains leading zeroes, remove them before returning
    - If no digits were removed during iteration and k is still greater than 0, remove the last k digits from the stack
*/


class Solution {
public:
    string removeKdigits(string num, int k) {
        if (k == num.size())
            return "0";

        stack<int> stack;

        for (int i = 0; i < num.length(); i++) {
            int digit = num[i] - '0';

            if (stack.empty()) {
                stack.push(digit);
            }
            else {
                // maintain a monotonic increasing stack till K
                while (!stack.empty() && stack.top() > digit && k > 0) {
                    stack.pop();
                    k--;
                }
                stack.push(digit);
            }
        }

        // Case 1: K != 0. i.e. I can still delete digits.
        // str = "12345" k = 2. In this case the stack will have 12345.
        // no digits are removed since monotonic increasing
        while (!stack.empty() && k > 0) {
            stack.pop();
            k--;
        }

        // if stack is empty then return "0"
        if (stack.empty())
            return "0";

        // accumulate the stack elements in a string.
        string smallestNum = "";
        while (!stack.empty()) {
            smallestNum += to_string(stack.top());
            stack.pop();
        }

        // Since stack follows LIFO, the string will be in reverse order.
        reverse(smallestNum.begin(), smallestNum.end());

        // Case 2: Check for valid number.
        int startIndex = 0;
        while (startIndex < smallestNum.length() &&
            smallestNum[startIndex] == '0')
            startIndex++;

        if (startIndex == smallestNum.length())
            return "0";

        return smallestNum.substr(startIndex);
    }
};

int main() {
    Solution obj;
    cout<<obj.removeKdigits("1432219", 3)<<endl;

    return 0;
}