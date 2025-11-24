#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
	Problem Statement:
	-----------------
	Write an algorithm to determine if a number n is happy.

	A happy number is a number defined by the following process:

	1. Starting with any positive integer, replace the number by the sum of the squares of its digits.
	2. Repeat the process until the number equals 1 (where it will stay), or it loops endlessly 
	   in a cycle which does not include 1.
	3. Those numbers for which this process ends in 1 are happy.

	Return true if n is a happy number, and false if not.


	Examples:
	---------
	Example 1:
	Input: n = 19
	Output: true
	Explanation:
	1^2 + 9^2 = 82
	8^2 + 2^2 = 68
	6^2 + 8^2 = 100
	1^2 + 0^2 + 02 = 1

	Example 2:
	Input: n = 2
	Output: false

	Approach:
	---------
	Approach 1: Use HashSet to store the seen squares, if any of the squares is seen again then
	there is a loop and we cannot reach 1. Return it as unhappy number

	e.g. -> 
	n = 2 
	2^2 = 4
	4^2 = 16
	1^2 + 6^2 = 37
	3^2 + 7^2 = 58
	5^2 + 8^2 = 89
	8^2 + 9^2 = 64 + 81 = 145
	1^2 + 4^2 + 5^2 = 42
	4^2 + 2^2 = 20
	2^2 + 0^2 = 4     (we have seen 4 before so the cycle repeats)

	T.C. - O(logN)
	S.C. - O(logN)
	
	The algorithm repeatedly calculates the sum of squares of digits until either reaching 1 or detecting a cycle. 
	For each number processed:
	1. Extracting digits takes O(log n) time (where n is the current number, as it has log₁₀(n) digits)
	2. The sequence of numbers will either reach 1 or enter a cycle within O(log n) iterations
	
	The key insight is that the sum of squares of digits reduces the number significantly. For a k-digit number, 
	the maximum sum of squares is 9² × k = 81k. Since k ≈ log₁₀(n), the numbers quickly become bounded. 
	Once bounded, the sequence must either reach 1 or cycle within a constant number of steps.

	Therefore, the overall time complexity is O(log n) iterations × O(log n) per iteration = O(log² n), 
	but since the numbers become small quickly after the first few iterations, the amortized complexity is O(log n).


	Approach 2:
	We use the Fast and Slow Pointer technique (also known as the "tortoise and hare" algorithm).
	
	slow = fast = num;
	while(true)
		fast = getNextNumber(getNextNumber(fast))
		slow = getNextNumber(slow)
		if (fast == 1)
			happy number
		if (fast == slow)
			not happy number;

	T.C. - O(logN)
	S.C. - O(1) - We use only two pointers regardless of input size.
*/

class Solution {
private:
	int getNextNumber(int n) {
		int sumOfSuqareOfDigits = 0;
		while (n != 0) {
			int digit = n % 10;
			n = n / 10;
			sumOfSuqareOfDigits = sumOfSuqareOfDigits + (digit*digit);
		}
		return sumOfSuqareOfDigits;
	}

public:
	bool isHappy1(int n) {
		if (n == 1)
			return true;

		unordered_set<int> seen;
		seen.insert(n);

		while (true) {
			n = getNextNumber(n);

			if (n == 1)
				return true;

			//if the number is seen is past then the cycle will continue
			if (seen.find(n) != seen.end())
				return false;
			seen.insert(n);
		}
	}

	bool isHappy2(int n) {
		if (n == 1)
			return true;
		
		int fast = n, slow = n;

		while (true) {
			fast = getNextNumber(getNextNumber(fast));
			slow = getNextNumber(slow);
			if (fast == 1)
				return true;
			if (fast == slow)
				return false;
		}
	}
};

int main() {
	Solution obj;
	obj.isHappy1(19) == true ? cout << "Happy Number" << endl : cout << "Not a Happy Number" << endl;
	obj.isHappy1(2)  == true ? cout << "Happy Number" << endl : cout << "Not a Happy Number" << endl;

	obj.isHappy2(19) == true ? cout << "Happy Number" << endl : cout << "Not a Happy Number" << endl;
	obj.isHappy2(7)  == true ? cout << "Happy Number" << endl : cout << "Not a Happy Number" << endl;
	return 0;
}