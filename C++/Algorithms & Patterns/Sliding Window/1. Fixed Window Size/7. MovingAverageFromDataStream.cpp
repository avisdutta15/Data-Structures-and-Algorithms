#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

	Examples:
	--------
	MovingAverage m = new MovingAverage(3);
	m.next(1) = 1
	m.next(10) = (1 + 10) / 2
	m.next(3) = (1 + 10 + 3) / 3
	m.next(5) = (10 + 3 + 5) / 3


	Approach:
	---------

*/

class MovingAverage {
	queue<int> Q;
	int K;
	int sum;
public:
	/** Initialize your data structure here. */
	MovingAverage(int size) {
		K = size;
		sum = 0;
	}

	double next(int val) {
		Q.push(val);
		sum = sum + val;
		if (Q.size() <= K)
			return (double)sum / Q.size();
		sum = sum - Q.front();
		Q.pop();
		return (double)sum / Q.size();
	}
};

int main() {
	MovingAverage obj(3);
	cout << obj.next(1)  << endl;
	cout << obj.next(10) << endl;
	cout << obj.next(3)  << endl;
	cout << obj.next(5)  << endl;
	return 0;
}