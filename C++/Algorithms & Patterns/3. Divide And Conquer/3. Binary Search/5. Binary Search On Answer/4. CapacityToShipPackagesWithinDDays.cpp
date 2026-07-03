#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>
#include <numeric>

using namespace std;

/*
	https://www.youtube.com/watch?v=rJ1Ih0BLRW0
	Problem Statement:
	-----------------
	A conveyor belt has packages that must be shipped from one port to another within days days.
	
	The ith package on the conveyor belt has a weight of weights[i]. 
	
	Each day, we load the ship with packages on the conveyor belt (in the order given by weights). 
	
	We may not load more weight than the maximum weight capacity of the ship.
	
	Return the least weight capacity of the ship that will result in all the packages on 
	the conveyor belt being shipped within days days.

 
	Examples:
	---------
	Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
	Output: 15
	Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
	1st day: 1, 2, 3, 4, 5
	2nd day: 6, 7
	3rd day: 8
	4th day: 9
	5th day: 10

	Note that the cargo must be shipped in the order given, so using a ship of capacity 
	14 and splitting the packages into parts like 
	(2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.

	Input: weights = [3,2,2,4,1,4], days = 3
	Output: 6
	Explanation: A ship capacity of 6 is the minimum to ship all the packages 
	in 3 days like this:
	1st day: 3, 2
	2nd day: 2, 4
	3rd day: 1, 4

	Input: weights = [1,2,3,1,1], days = 4
	Output: 3
	Explanation:
	1st day: 1
	2nd day: 2
	3rd day: 3
	4th day: 1, 1

	Constraints:
	------------

	Approach:
	--------
	Minimum capacity: max(weights[])
		The ship must carry each package individually at minimum. 
		If capacity < max weight, that package can never be shipped. 
		So the lower bound is the heaviest package.

	Maximum capacity: sum(weights[])
		If the ship can carry everything in 1 day, that's the worst 
		case we'd ever need. Any capacity beyond this is wasteful since D >= 1.
		
		Why this forms a valid binary search space:
			At capacity = max(weights) → may need many days (could be > D)
			At capacity = sum(weights) → always ships in exactly 1 day
		
	The function daysNeeded(capacity) is monotonically decreasing — as capacity increases, 
	days needed decreases or stays the same. 
	
	This monotonicity is what makes binary search valid on this range.

	So the search space is [max(weights), sum(weights)] 
	and we binary search for the minimum capacity where daysNeeded(capacity) <= D.	
*/

class Solution100 {
public:
	int calculate(string s) {
		stack<int> stack;
		int currentNumber = 0;
		int N = s.length();
		int previousOperator = '+';		// Initialize with '+' to handle the first number

		for (int i = 0; i < N; i++) {

			char currentChar = s[i];

			// Build multi-digit numbers
			if (isdigit(currentChar)) {
				currentNumber = currentNumber * 10 + (currentChar - '0');
			}

			// Process when we encounter an operator or reach the end of string
			// Note: We also need to check i == n - 1 to process the last number
			if (currentChar == '+' || currentChar == '-' || 
				currentChar == '*' || currentChar == '/' || i == N - 1) {
				
				if (previousOperator == '+') {
					stack.push(currentNumber);
				}
				else if (previousOperator == '-') {
					stack.push(-currentNumber);
				}
				else if (previousOperator == '*') {
					int previousNumber = stack.top();
					stack.pop();
					stack.push(previousNumber * currentNumber);
				}
				else if (previousOperator == '/') {
					int previousNumber = stack.top();
					stack.pop();
					stack.push(previousNumber / currentNumber);
				}

				// Update operator for next iteration
				currentNumber = 0;
				// Update operator for next iteration
				previousOperator = currentChar;
			}
		}

		// Sum all numbers in the stack to get the final result
		int result = 0;
		while (!stack.empty()) {
			result = result + stack.top();
			stack.pop();
		}

		return result;
	}
};

class Solution1 {
private:
	bool canWeShipWithWeightIOnGivenDays(int weight, vector<int>& weights, int days) {

		int daysNeeded = 1;
		int currentLoad = 0;

		for (int weightOfAPackage : weights) {
			// If currentLoad + weightOfAPackage <= weight, we can add it to the current day
			if (currentLoad + weightOfAPackage <= weight) {
				currentLoad += weightOfAPackage;
			}
			else {
				// If currentLoad + weightOfAPackage > weight, we need a new day
				// and reset the currentLoad to the weightOfAPackage
				daysNeeded++;
				currentLoad = weightOfAPackage;
			}
		}

		return daysNeeded <= days;

	}
public:
	int shipWithinDays(vector<int>& weights, int days) {

		int minimumWeightThatWeCanShip = *max_element(weights.begin(), weights.end());
		int maximumWeightThatWeCanShip = accumulate(weights.begin(), weights.end(), 0);

		for (int weight = minimumWeightThatWeCanShip; weight <= maximumWeightThatWeCanShip; weight++) {
			if (canWeShipWithWeightIOnGivenDays(weight, weights, days) == true) {
				return weight;
			}
		}

		return -1;
	}
};

class Solution2 {
private:
	bool canWeShipWithWeightIOnGivenDays(int weight, vector<int>& weights, int days) {

		int daysNeeded = 1;
		int currentLoad = 0;

		for (int weightOfAPackage : weights) {
			// If currentLoad + weightOfAPackage <= weight, we can add it to the current day
			if (currentLoad + weightOfAPackage <= weight) {
				currentLoad += weightOfAPackage;
			}
			else {
				// If currentLoad + weightOfAPackage > weight, we need a new day
				// and reset the currentLoad to the weightOfAPackage
				daysNeeded++;
				currentLoad = weightOfAPackage;
			}
		}

		return daysNeeded <= days;

	}
public:
	int shipWithinDays(vector<int>& weights, int days) {

		int minimumWeightThatWeCanShip = *max_element(weights.begin(), weights.end());
		int maximumWeightThatWeCanShip = accumulate(weights.begin(), weights.end(), 0);

		int lo = minimumWeightThatWeCanShip;
		int hi = maximumWeightThatWeCanShip;
		int minimumWeightCapacityOfShip = -1;

		while(lo <= hi){
			int mid = lo + (hi - lo) / 2;
			if(canWeShipWithWeightIOnGivenDays(mid, weights, days) == true){
				minimumWeightCapacityOfShip = mid;
				hi = mid - 1;	// Explore left half to minimize the weight of ship
			}else{
				lo = mid + 1;
			}
		}

		return minimumWeightCapacityOfShip;
	}
};


int main() {
	Solution1 obj;
	vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	cout << obj.shipWithinDays(weights, 5) << endl;
	return 0;
}