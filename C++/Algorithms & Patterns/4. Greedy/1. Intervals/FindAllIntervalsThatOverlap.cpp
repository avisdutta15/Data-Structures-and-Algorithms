#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------

	Examples:
	---------

	Approach:
	---------
*/

class Solution {
public:
	vector<pair<int, int>> findAllIntervalsThatOverlap(vector<pair<int, int>> intervals) {
		vector<pair<int, int>> allOverlappingIntervals;

		//base case: empty list
		if (intervals.size() == 0)
			return allOverlappingIntervals;

		//sort the intervals based on start time
		auto comp = [](const pair<int, int> &a, const pair<int, int> &b) {
			return a.first < b.first;
			};
		sort(intervals.begin(), intervals.end(), comp);

		//iterate and find overlapping
		for (int i = 1; i < intervals.size(); i++) {
			if (intervals[i].first <= intervals[i - 1].second) {
				allOverlappingIntervals.push_back(intervals[i]);
				allOverlappingIntervals.push_back(intervals[i-1]);
			}
		}

		return allOverlappingIntervals;
	}
};

int main() {
	Solution obj;
	vector<pair<int, int>> intervals = { {1, 3}, {5, 7}, {2, 4}, {6, 8}, {9, 10} };
	vector<pair<int, int>> result = obj.findAllIntervalsThatOverlap(intervals);
	for (auto p : result) {
		cout << p.first << " " << p.second << endl;
	}
	return 0;
}