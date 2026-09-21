#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an integer array prices where prices[i] is the price of the ith item in a shop.

	There is a special discount for items in the shop. If you buy the ith item, then you will 
	receive a discount equivalent to prices[j] where j is the minimum index such that j > i and 
	prices[j] <= prices[i]. Otherwise, you will not receive any discount at all.

	Return an integer array answer where answer[i] is the final price you will pay for the ith item 
	of the shop, considering the special discount.

	Examples:
	---------
	Example 1:
	Input: prices = [8,4,6,2,3]
	Output: [4,2,4,2,3]
	Explanation: 
	For item 0 with price[0]=8 you will receive a discount equivalent to prices[1]=4, therefore, the final price you will pay is 8 - 4 = 4.
	For item 1 with price[1]=4 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 4 - 2 = 2.
	For item 2 with price[2]=6 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 6 - 2 = 4.
	For items 3 and 4 you will not receive any discount at all.
	
	Example 2:
	Input: prices = [1,2,3,4,5]
	Output: [1,2,3,4,5]
	Explanation: In this case, for all items, you will not receive any discount at all.
	
	Example 3:
	Input: prices = [10,1,1,6]
	Output: [9,0,1,6]

	Approach:
	--------
	To calculate the discount of a given i, we need to find the next smaller or equal price to the right of i.

	T.C. - O(n). S.C. - O(n)
*/

class Solution {
public:
	vector<int> finalPrices(vector<int>& prices) {
		if (prices.size() == 0)
			return vector<int>();

		stack<int> stack;
		vector<int> finalPrice(prices.begin(), prices.end());
		int n = prices.size();

		for (int i = n - 1; i >= 0; i--) {
			if (stack.empty()) {
				finalPrice[i] = prices[i];
				stack.push(prices[i]);
			}
			else if (stack.top() < prices[i]) {
				finalPrice[i] = prices[i] - stack.top();
				stack.push(prices[i]);
			}
			else {
				//stack.top() > prices[i] and not stack.top() >= prices[i]
				//because as soon as we get a j such that price[i] <= price[j], we stop
				//if we do stack.top() >= prices[i] we will loose the first price[j] which is equal to price[i]
				while (!stack.empty() && stack.top() > prices[i])
					stack.pop();
				if (stack.empty())
					finalPrice[i] = prices[i];
				else
					finalPrice[i] = prices[i] - stack.top();
				stack.push(prices[i]);
			}

		}
		return finalPrice;
	}
};

int main() {
	Solution obj;

	//Test 1
	vector<int>prices = { 8,4,6,2,3 };
	auto finalPrice = obj.finalPrices(prices);

	cout << "Price: " << "\t\t";
	for (auto i : prices) {
		cout << i << " ";
	}
	cout << endl;
	cout << "Final Price: " << "\t";
	for (auto i : finalPrice) {
		cout << i << " ";
	}
	cout << endl;

	//Test 2
	prices = { 1,2,3,4,5 };
	finalPrice = obj.finalPrices(prices);

	cout << "Price: " << "\t\t";
	for (auto i : prices) {
		cout << i << " ";
	}
	cout << endl;
	cout << "Final Price: " << "\t";
	for (auto i : finalPrice) {
		cout << i << " ";
	}
	cout << endl;

	//Test 3
	prices = { 10,1,1,6 };
	finalPrice = obj.finalPrices(prices);

	cout << "Price: " << "\t\t";
	for (auto i : prices) {
		cout << i << " ";
	}
	cout << endl;
	cout << "Final Price: " << "\t";
	for (auto i : finalPrice) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}