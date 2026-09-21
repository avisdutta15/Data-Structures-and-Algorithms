#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
	Problem Statement:
	-----------------
	Design an algorithm that collects daily price quotes for some stock and returns the span of that
	stock's price for the current day.

	The span of the stock's price in one day is the maximum number of consecutive days (starting from
	that day and going backward) for which the stock price was less than or equal to the price of that
	day.

	1. For example, if the prices of the stock in the last four days is [7,2,1,2] and the price of the
	   stock today is 2, then the span of today is 4 because starting from today, the price of the stock
	   was less than or equal 2 for 4 consecutive days.
	2. Also, if the prices of the stock in the last four days is [7,34,1,2] and the price of the stock
	   today is 8, then the span of today is 3 because starting from today, the price of the stock was
	   less than or equal 8 for 3 consecutive days.

	Implement the StockSpanner class:

	1. StockSpanner() Initializes the object of the class.
	2. int next(int price) Returns the span of the stock's price given that today's price is price.

	Examples:
	---------
	Input:		["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
				[[], [100], [80], [60], [70], [60], [75], [85]]
	Output: 	[null, 1, 1, 1, 2, 1, 4, 6]

	Explanation:
	StockSpanner stockSpanner = new StockSpanner();
	stockSpanner.next(100); // return 1
	stockSpanner.next(80);  // return 1
	stockSpanner.next(60);  // return 1
	stockSpanner.next(70);  // return 2
	stockSpanner.next(60);  // return 1
	stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were 
							//			 less than or equal to today's price.
	stockSpanner.next(85);  // return 6

	Approach:
	--------
	span = maximum number of consecutive days (starting from that day and going backward) for which the 
		   stock price was less than or equal to the price of that day.
	
	The idea is to check, for each day, how many consecutive previous days had stock prices less than 
	or equal to the current day’s price. This can be done by moving leftwards from the current index until 
	a higher price is found or the beginning of the array is reached.
	
	T.C - O(N^2) S.C. - O(N)
	
	A better approach
	The idea is to use a stack to directly find this first previous greater element for every day, 
	instead of checking all consecutive smaller ones. Once we know that index, we can compute the span as:
		span[i] = currentIndex − indexOfPreviousGreaterElement
	e.g.span[3] = 3 - 1		i.e. span of 70 = indexof(70) - indexOfPreviousGreaterElement(100)
		        = 2
	Note:
		In case, there is no previous greater on left, that means it is greater than all of the previous days.
		So in that case, span[i] = i+1

	T.C. - O(n). S.C. - O(n)
*/

class StockSpanner {
	vector<int> prices;
	stack<int> stack;
	int i = -1;
public:
	StockSpanner() {
	}

	int next(int price) {
		prices.push_back(price);
		i++;

		if (stack.empty()) {
			stack.push(i);
			return i+1;			
		}
		else if (prices[stack.top()] > price) {
			stack.push(i);
			return prices.size() - stack.top();
		}
		else {
			while (!stack.empty() && prices[stack.top()] <= price)
				stack.pop();
			if (stack.empty()) {
				stack.push(i);
				return i+1;
			}
			else {
				int span = i - stack.top();
				stack.push(i);
				return span;
			}
		}
	}
};

//A cleaned up version.
class StockSpanner2{
	//stack<index, element>
	stack<pair<int,int>> stack;
	int i = -1;
public:
	StockSpanner2() {
	}

	int next(int price) {
		i++;
		int span = i+1;
		if (stack.empty()) {
			stack.push({ i, price });
		}
		else if (stack.top().second > price) {
			span = i - stack.top().first;
			stack.push({ i, price });
		}
		else {
			while (!stack.empty() && stack.top().second <= price)
				stack.pop();
			if (stack.empty()) {
				stack.push({ i, price });
			}
			else {
				span = i - stack.top().first;
				stack.push({ i, price });
			}
		}
		return span;
	}
};


int main() {
	StockSpanner obj;
	cout << obj.next(100) << endl;
	cout << obj.next(80) << endl;
	cout << obj.next(60) << endl;
	cout << obj.next(70) << endl;
	cout << obj.next(60) << endl;
	cout << obj.next(75) << endl;
	cout << obj.next(85) << endl;

	cout << endl;
	StockSpanner2 obj1;
	cout << obj1.next(31) << endl;
	cout << obj1.next(41) << endl;
	cout << obj1.next(48) << endl;
	cout << obj1.next(59) << endl;
	cout << obj1.next(79) << endl;
	return 0;
}