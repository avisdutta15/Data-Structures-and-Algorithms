#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an array of meeting time intervals where each interval is represented as [start, end].
	You need to determine if a person can attend all the meetings without any overlap. Essentially, you
	are asked whether there are any overlaps between the meetings.




	Examples:
	---------
	Input: [[0, 30], [5, 10], [15, 20]]
	Output: False
	In this example, meetings overlap, so the output is False. If all meetings were non-overlapping, the output would be True.


	Approach 1 : Brute Force
	-------------------------
	Iterate the list and check if every pair overlaps. i.e. meeting[i] overlaps with meeting[i+1], [i+2]....
											Then			meeting[i+1] overlaps with meeting[i+2], [i+3]...
	Time Complexity : O(n^2),
	Space Complexity : O(1)

	Approach 2: Better
	------------------
	Check whether all meetings can be attended without time conflicts by first sorting the meeting intervals 
	based on their start times. After sorting, it compares each meeting's end time with the next meeting's start 
	time to detect any overlaps. 
	
	If an overlap is found, it returns false, indicating a scheduling conflict. 
	
	Otherwise, it returns true, meaning all meetings can be attended without overlaps.

	Time Complexity : O(nlogn),
	Space Complexity : O(1)
*/

class Solution1 {
private:
	bool overlap(vector<int>& a, vector<int>& b) {
		return max(a[0], b[0]) <= min(a[1], b[1]);
	}
public:
	bool canAttendMeetings(vector<vector<int>>& intervals) {
		for (int i = 0; i < intervals.size() - 1; i++) {
			for (int j = i + 1; j < intervals.size(); j++) {
				if (overlap(intervals[i], intervals[j]))
					return false;
			}
		}
		return true;
	}
};

class Solution2 {
private:
	bool overlap(vector<int>& a, vector<int>& b) {
		return max(a[0], b[0]) <= min(a[1], b[1]);
	}
public:
	bool canAttendMeetings(vector<vector<int>>& intervals) {
		sort(intervals.begin(), intervals.end());
		for (int i = 0; i < intervals.size() - 1; i++) {
			if (overlap(intervals[i], intervals[i + 1]))
				return false;
		}
		return true;
	}
};

int main()
{
	Solution1 obj1;
	vector<vector<int>> intervals = { {0,30}, {5,10}, {15,20} };
	auto result = obj1.canAttendMeetings(intervals);

	cout << result << endl;

	Solution2 obj2;
	intervals = { {0,30}, {5,10}, {15,20} };
	result = obj2.canAttendMeetings(intervals);

	cout << result << endl;

	return 0;
}