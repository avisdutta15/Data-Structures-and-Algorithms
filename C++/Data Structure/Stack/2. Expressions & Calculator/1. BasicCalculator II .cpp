#include <iostream>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Implement a basic calculator to evaluate a simple expression string.
	The expression string contains only non-negative integers, +, -, *, /
	operators and empty spaces . The integer division should truncate toward zero.

	Note:
	You may assume that the given expression is always valid.
	Do not use the eval built-in library function.


	Examples:
	---------
	Example 1:
	Input: "3+2*2"
	Output: 7

	Example 2:
	Input: " 3/2 "
	Output: 1

	Example 3:
	Input: " 3+5 / 2 "
	Output: 5
	
	Intuition:
	----------
	The key challenge is handling operator precedence - multiplication and division must be evaluated 
	before addition and subtraction. If we try to evaluate the expression from left to right in a 
	single pass, we'd get incorrect results for expressions like "3+2*2".

	Think about how we'd manually evaluate "3+5*2-6/3":

	First, we'd identify all the multiplication and division operations: 5*2=10 and 6/3=2
	Then we'd be left with "3+10-2"
	Finally, we'd evaluate from left to right: 3+10-2=11
	This suggests we need a two-phase approach: handle * and / first, then handle + and -. But how 
	can we do this in a single pass?

	The insight is to use a stack to defer the final addition/subtraction until we've handled all 
	multiplications and divisions. When we encounter:

	A + or -: We can safely push the number to the stack (with appropriate sign) because these 
	operations have the lowest precedence A * or /: We must immediately compute it with the 
	previous number (top of stack) since these 	have higher precedence

	For example, with "3+5*2":
		See 3 with + sign → push 3 to stack: [3]
		See 5 with + sign → push 5 to stack: [3, 5]
		See 2 with * sign → pop 5, compute 5*2=10, push back: [3, 10]
	Sum the stack: 3+10=13
	The clever part is tracking the operator that comes before each number. This tells us what to 
	do with that number when we finish reading it. By processing multiplication/division immediately 
	but deferring addition/subtraction to the stack, we naturally handle operator precedence in a 
	single pass


	Approach:
	---------
	We traverse the string s using a stack-based approach. The key variables are:

	stack: A stack to store numbers that will be summed at the end
	num: Current number being built from consecutive digits
	previousOperator: The operator before the current number (initialized as +)
	
	The algorithm works as follows:
	1. Iterate through each character in the string:
		A. If it's a digit, build the current number: num = num * 10 + int(c)
		B. If it's an operator ('+''-''*''/') or we've reached the end of the string, process the completed number
	2. Process the number based on the previous operator (previousOperator) :
		+: Push the number directly to the stack : stk.append(num)
		- : Push the negative of the number : stk.append(-num)
		* : Pop the top element, multiply with current number, push result : stk.append(stk.pop()* num)
		/ : Pop the top element, divide by current number, push result : stk.append(int(stk.pop() / num))
	3. Update for next iteration :
		Set previousOperator to the current operator for the next number
		Reset num = 0 to start building the next number
	4. Return the final result : Sum all elements in the stack

	Example walkthrough for "3+5*2-6/3" :
		Process 3 with sign + : stack = [3]
		Process 5 with sign + : stack = [3, 5]
		Process 2 with sign * : pop 5, compute 5 * 2 = 10, stack = [3, 10]
		Process 6 with sign - : stack = [3, 10, -6]
		Process 3 with sign / : pop - 6, compute - 6 / 3 = -2, stack = [3, 10, -2]
		Return sum : 3 + 10 + (-2) = 11

    Reference:
    ----------
    https://www.youtube.com/watch?v=b_vCkD-rhiU
*/

class Solution {
public:
	int calculate(string str) {
		int n = str.size();

		int number = 0;
		char previousOperator = '+';	// Initialize with '+' to handle the first number
		stack<int> stack;

		for (int i = 0; i < n; i++) {
			char currentCharacter = str[i];

			// if the current character is space then don't do anything
			if (currentCharacter == ' ')
				continue;

			// build the number
			if (isdigit(currentCharacter)) {
				number = number * 10 + (currentCharacter - '0');
			}

			// if we are at the last character of the string or
			// if the current character is an operator 
			//		then process the previous operator and push the number to the stack
			if (i == n-1 || currentCharacter == '+' || currentCharacter == '-' || currentCharacter == '*' || currentCharacter == '/') {

				if (previousOperator == '+') {
					// Push positive number to stack
					stack.push(number);
				}
				else if (previousOperator == '-') {
					// Push negative number to stack
					stack.push(-1 * number);
				}
				else if (previousOperator == '*') {
					// Multiply with the top of stack
					int top = stack.top();
					stack.pop();
					stack.push(top * number);
				}
				else if (previousOperator == '/') {
					// Divide the top of stack by current number
					int top = stack.top();
					stack.pop();
					stack.push(top / number);
				}

				// Reset current number for next parsing
				number = 0;
				// Store the current operator in the previous operator variable for next iteration
				previousOperator = currentCharacter;
			}
		}

		// Sum all numbers in the stack to get the final result
		int answer = 0;
		while (!stack.empty()) {
			answer = answer + stack.top();
			stack.pop();
		}
		return answer;
	}
};

int main() {
	Solution obj;
	cout << obj.calculate("1+1+1") << endl;
	cout << obj.calculate("3+2*5") << endl;
	cout << obj.calculate("3/2") << endl;
	cout << obj.calculate("3+5 / 2") << endl;
	return 0;
}