#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] of daily stock prices, the stock span for the i-th day is the count of
	consecutive days up to and including day i, such that each of those days had a stock price
	less than or equal to the price on day i.

	Examples:
	---------
	Input: arr[] = [100, 80, 60, 120]
	Output: [1, 1, 1, 4]
	Explanation: For 100, there are no previous higher prices, so span = 1. For 80 and 60,
	each is smaller than the previous, so their spans remain 1. For 120, it is greater than
	all earlier prices (100, 80, 60), so the span extends back across all four days, giving
	span = 4.

	Input: arr[] = [10, 4, 5, 90, 120, 80]
	Output: [1, 1, 2, 4, 5, 1]
	Explanation: For 10 and 4, no earlier prices are smaller, so span = 1 each. For 5, it is
	greater than 4, so span = 2. For 90, it is greater than 10, 5, and 4, so span = 4. For 120,
	it is greater than all previous prices, giving span = 5. Finally, 80 is smaller than 120,
	so span = 1.

	Approach:
	---------
	BruteForce:
	The idea is to check, for each day, how many consecutive previous days had stock prices less 
	than or equal to the current day’s price. This can be done by moving leftwards from the current 
	index until a higher price is found or the beginning of the array is reached.
	T.C - O(N^2) S.C. - O(1)

	Optimized:
	In the previous approach, for each day we kept moving leftward and comparing prices one by one. 
	We continued as long as the current day’s price was greater than or equal to the previous day’s price. 
	But the moment we find a price greater than the current day’s price, we stop.
	That means we are always stopping at the Next Greater Element To Left (Monotonically Decreasing Stack).

	The idea is to use a stack to directly find this first previous greater element for every day, 
	instead of checking all consecutive smaller ones. Once we know that index, we can compute the span as:

						Span[i] = i − indexOfPreviousGreaterElement

	Illustration:
	-------------
	price[] = {10, 4, 5, 90, 120, 80}

	Initial: Stack = empty, Result = []
	Day 0: Price = 10
	Stack empty → Span = 0 + 1 = 1
	Push index 0
	Stack: [0], Result: [1]

	Day 1: Price = 4
	Stack top (price 10) > 4 → Stop popping
	Span = 1 - 0 = 1
	Push index 1
	Stack: [0, 1], Result: [1, 1]

	Day 2: Price = 5
	Stack top (price 4) ≤ 5 → Pop index 1
	Stack top (price 10) > 5 → Stop popping
	Span = 2 - 0 = 2
	Push index 2
	Stack: [0, 2], Result: [1, 1, 2]

	Day 3: Price = 90
	Stack top (price 5) ≤ 90 → Pop index 2
	Stack top (price 10) ≤ 90 → Pop index 0
	Stack empty → Span = 3 + 1 = 4
	Push index 3
	Stack: [3], Result: [1, 1, 2, 4]

	Day 4: Price = 120
	Stack top (price 90) ≤ 120 → Pop index 3
	Stack empty → Span = 4 + 1 = 5
	Push index 4
	Stack: [4], Result: [1, 1, 2, 4, 5]

	Day 5: Price = 80
	Stack top (price 120) > 80 → Stop popping
	Span = 5 - 4 = 1
	Push index 5
	Stack: [4, 5], Result: [1, 1, 2, 4, 5, 1]
*/

class Solution {
public:
	vector<int> stockSpanBruteForce(vector<int>& price) {
		if (price.size() == 0)
			return vector<int>();

		vector<int> stockSpan(price.size(), 1);
		int daysWithLessOrEqualPrice = 0;

		for (int i = 0; i < price.size(); i++) {
			daysWithLessOrEqualPrice = 1;

			// move left and stop once you move out of array or find a 
			// day with price greater than today's price
			for (int j = i - 1; j >= 0; j--) {
				if (price[j] <= price[i])
					daysWithLessOrEqualPrice++;
				else
					break;
			}
			stockSpan[i] = daysWithLessOrEqualPrice;
		}
		return stockSpan;
	}

	vector<int> stockSpanOptimized(vector<int>& price) {
		if (price.size() == 0)
			return vector<int>();

		vector<int> stockSpan(price.size(), 1);
		stack<int> stack;

		for (int i = 0; i < price.size(); i++) {

			//e.g. price[] = {1, 2, 3}, i = 2, so stack is empty [].
			//	   stockspan[2] = 3 {1, 2, 3} i.e. i + 1 
			if (stack.size() == 0) {
				stockSpan[i] = i+1;
				stack.push(i);
			}
			else if (price[i] < price[stack.top()]) {
				stockSpan[i] = i - stack.top();
				stack.push(i);
			}
			else {
				while (stack.size() != 0 && price[i] > price[stack.top()]) {
					stack.pop();
				}
				if (stack.size() == 0) {
					stockSpan[i] = i+1;
					stack.push(i);
				}
				else{
					stockSpan[i] = i - stack.top();
					stack.push(i);
				}
			}
		}
		return stockSpan;
	}
};

int main() {
	Solution obj;

	//Test 1
	vector<int> price = { 100, 80, 60, 120 }; 
	vector<int> stockSpan = obj.stockSpanBruteForce(price);
	for (int i : stockSpan) {
		cout << i << " ";
	}
	cout << endl;

	//Test 2
	price = { 10, 4, 5, 90, 120, 80 };
	stockSpan = obj.stockSpanBruteForce(price);
	for (int i : stockSpan) {
		cout << i << " ";
	}
	cout << endl;

	//Test 3
	price = { 100, 80, 60, 120 };
	stockSpan = obj.stockSpanOptimized(price);
	for (int i : stockSpan) {
		cout << i << " ";
	}
	cout << endl;

	//Test 4
	price = { 10, 4, 5, 90, 120, 80 };
	stockSpan = obj.stockSpanOptimized(price);
	for (int i : stockSpan) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}