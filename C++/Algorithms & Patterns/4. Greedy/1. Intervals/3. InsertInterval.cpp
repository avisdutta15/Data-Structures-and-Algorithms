#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an array of non-overlapping intervals intervals where 
	intervals[i] = [starti, endi] 
	represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. 
	You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

	Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals 
	still does not have any overlapping intervals (merge overlapping intervals if necessary).

	Return intervals after the insertion.

	Note that you don't need to modify intervals in-place. You can make a new array and return it.

	Examples:
	---------
	Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
	Output: [[1,5],[6,9]]

	Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
	Output: [[1,2],[3,10],[12,16]]
	Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

	Approach:
	---------
	Insert intervals before the new interval:
		Go through the intervals that end before the new interval starts. These intervals do not overlap and can be directly added to the result.
	Merge overlapping intervals into the new interval:
		Look at the intervals that start before or at the same time the new interval ends. These intervals overlap with the new interval and need to be merged.
		Update the new interval's start time to the earliest start time and its end time to the latest end time among the overlapping intervals.
	Add the merged interval:
		Once all overlapping intervals have been merged, add the updated new interval to the result.
	Insert remaining intervals:
		Add any intervals that start after the new interval ends. These intervals do not overlap and can be directly added to the result.

	Return the result: The result array now contains the updated list of intervals, with the new interval correctly inserted and merged.

	Time Complexity : O(n), 
	Space Complexity : O(n)
*/


class Solution {
private:
	bool overlap(vector<int>& a, vector<int>& b) {
		return max(a[0], b[0]) <= min(a[1], b[1]);
	}
public:
	vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		vector<vector<int>> newIntervals;
		
		int i = 0;

		// Insert intervals before newInterval
		while(i<intervals.size() && intervals[i][1] < newInterval[0]) {
			newIntervals.push_back(intervals[i]);
			i++;
		}

		// Merge overlapping intervals into the new interval
		while(i < intervals.size()){
			if (overlap(intervals[i], newInterval)) {
				newInterval[0] = min(intervals[i][0], newInterval[0]);
				newInterval[1] = max(intervals[i][1], newInterval[1]);
				i++;
			}
			else {
				break;
			}
		}
		
		//Insert the merged interval Add the merged interval to the result vector
		newIntervals.push_back(newInterval);

		//Insert remaining intervals after newInterval
		for (; i < intervals.size(); i++) {
			newIntervals.push_back(intervals[i]);
		}
		return newIntervals;
	}
};

int main()
{
	Solution obj;
	vector<vector<int>> intervals = { {1, 3}, {6, 9}};
	vector<int> newInterval = { 2, 5 };
	vector<vector<int>> result = obj.insert(intervals, newInterval);
	for (auto p : result) {
		cout << p[0] << " " << p[1] << endl;
	}
	cout << endl;

	intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
	newInterval = { 4,8 };
	result = obj.insert(intervals, newInterval);
	for (auto p : result) {
		cout << p[0] << " " << p[1] << endl;
	}
	cout << endl;

	return 0;
}