#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, 
	and return an array of the non-overlapping intervals that cover all the intervals in the input.

	Examples:
	---------
	Example 1:
	Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
	Output: [[1,6],[8,10],[15,18]]
	Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
	
	Example 2:
	Input: intervals = [[1,4],[4,5]]
	Output: [[1,5]]
	Explanation: Intervals [1,4] and [4,5] are considered overlapping.
	
	Example 3:
	Input: intervals = [[4,7],[1,4]]
	Output: [[1,7]]
	Explanation: Intervals [1,4] and [4,7] are considered overlapping.

	Approach:
	---------
	Sort the intervals according to starting time. Once we have the sorted intervals,
	we can combine all intervals in a linear traversal. The idea is, in sorted array of
	intervals, if interval[i] doesn’t overlap with interval[i-1], then interval[i+1]
	cannot overlap with interval[i-1] because starting time of interval[i+1] must be greater
	than or equal to interval[i].
	
	How to say two are overlapping?
	{1, 8}, {2, 6} = A[index-1].end>=A[i].start
	
	How to merge them?
	{1, 8}, {2, 6} = {1, 8}   start = min of both start, end = max of both start

	Optimization:
		Sort all intervals in increasing order of start time.
		Traverse sorted intervals starting from the first interval,
		Do the following for every interval.
			1. If the current interval is not the first interval and it overlaps
			with the previous interval, then merge it with the previous interval.
			Keep doing it while the interval overlaps with the previous one.
			2. If the current interval does not overlap with the previous interval,
			move to the next interval.
*/

class Solution {
private:
	//if max(start times) <= min(end times)
	bool overlap(const vector<int>& a, const vector<int>& b) {
		return max(a[0], b[0]) <= min(a[1], b[1]);
	}
public:
	//TC: O(NLogN) SC: O(N)
	vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>>& intervals) {
		
		//sort the intervals based on start time
		sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
			return a[0] < b[0];
			});
		
		//Keep a stack to store and merge the intervals. Push the first interval.
		stack<vector<int>> stack;
		stack.push(intervals[0]);
		
		//for the rest of the intervals
		for (int i = 1; i < intervals.size(); i++) {
			//get the last interval i.e. the top of the stack and the current interval
			vector<int> intervala = stack.top();
			vector<int> intervalb = intervals[i];

			//if they overlap then merge them and insert the merged
			if (overlap(intervala, intervalb)==true) {
				stack.pop();
				intervala[0] = min(intervala[0], intervalb[0]);
				intervala[1] = max(intervala[1], intervalb[1]);
				stack.push(intervala);
			}
			else {
				//else insert the interval
				stack.push(intervalb);
			}
		}

		//transfer all the intervals from stack to a resultant vector.
		vector<vector<int>> mergedIntervals;
		while (!stack.empty()) {
			mergedIntervals.push_back(stack.top());
			stack.pop();
		}

		//reverse the vector to maintain the original order as stack popped LIFO.
		reverse(mergedIntervals.begin(), mergedIntervals.end());

		return mergedIntervals;
	}

	//TC: O(NLogN) SC: O(1)
	vector<vector<int>> mergeOverlappingIntervalsOptimized(vector<vector<int>>& intervals) {
		//sort the meetings based on their start time
		sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
			return a[0] < b[0];
		});

		//last denotes the last interval in the final merged list.
		//Initially there is no interval in the final list, so we set last = -1.
		int last = -1;
		for (int i = 0; i < intervals.size(); i++) {
			//if it is first interval then copy as it is.
			if (i == 0) {
				intervals[last + 1] = intervals[i];
				last++;
			}
			//check if it overlaps with any of the previous intervals
			else if (overlap(intervals[last], intervals[i])) {
				while (last >= 0 && overlap(intervals[last], intervals[i])) {
					intervals[last][0] = min(intervals[last][0], intervals[i][0]);
					intervals[last][1] = max(intervals[last][1], intervals[i][1]);
					last--;
				}

				//suppose last was at 1. after merging i with 1 we made last-- i.e. last = 0. 
				//But we have to insert the merged interval at last + 1 position. i.e. at position 1.
				//So we need to do last++ to make it 1 again.
				last++;
			}
			//if no overlap then copy as it is.
			else {
				intervals[last + 1] = intervals[i];
				last++;
			}
		}

		//last is 0 based index. So if last is standing at 0, it means size is last + 1 = 0 + 1 = 1. 
		//So we need to return size = last + 1 elements. Hence the range [begin, begin + last + 1).
		return vector<vector<int>>(intervals.begin(), intervals.begin() + last + 1);
	}
};

int main() {
	Solution obj;
	vector<vector<int>> intervals = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };
	vector<vector<int>> result = obj.mergeOverlappingIntervalsOptimized(intervals);
	for (auto p : result) {
		cout << p[0] << " " << p[1] << endl;
	}
	cout << endl;

	intervals = { {1,4}, {4,5} };
	result = obj.mergeOverlappingIntervalsOptimized(intervals);
	for (auto p : result) {
		cout << p[0] << " " << p[1] << endl;
	}
	cout << endl;

	intervals = { {4, 7}, {1,4} };
	result = obj.mergeOverlappingIntervalsOptimized(intervals);
	for (auto p : result) {
		cout << p[0] << " " << p[1] << endl;
	}
	cout << endl;
	return 0;
}