#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	You are given timings of n meetings in the form of (start[i], end[i]) where start[i] is the start time of
	meeting i and end[i] is the finish time of meeting i. Return the maximum number of meetings that can be accommodated
	in a single meeting room, when only one meeting can be held in the meeting room at a particular time.

	Note: The start time of one chosen meeting can't be equal to the end time of the other chosen meeting.

	Examples:
	Input: start[] = [1, 3, 0, 5, 8, 5],
		   end[]   = [2, 4, 6, 7, 9, 9]
	Output: 4
	Explanation: Maximum four meetings can be held with given start and end timings.
				 The meetings are - (1, 2), (3, 4), (5,7) and (8,9)

	Input: start[] = [10, 12, 20],
		   end[]   = [20, 25, 30]
	Output: 1
	Explanation: Only one meetings can be held with given start and end timings.

	Input: start[] = [1, 2],
		   end[] = [100, 99]
	Output: 1

	Approach:
	The greedy approach works perfectly here because the best strategy is always to select the meeting that finishes earliest.
	Why does this work?
	If a meeting ends early, the room becomes available sooner, allowing more meetings to fit in.
	By always picking the meeting with the smallest finishing time that does not overlap with previously
	chosen meetings, we maximize the number of scheduled meetings.

*/


class Solution {
	struct Meeting {
		int start, end, pos;
		Meeting(int start, int end, int pos) {
			this->start = start;
			this->end = end;
			this->pos = pos;
		}
	};
public:
	int maxMeetings(vector<int>& start, vector<int>& end) {
		vector<Meeting> meetings;
		for (int i = 0; i < start.size(); i++) {
			meetings.push_back(Meeting(start[i], end[i], i + 1));
		}

		// Sort meetings based on their end times
		sort(meetings.begin(), meetings.end(), [](Meeting& a, Meeting& b) {
			return a.end < b.end;
			});

		int lastEnd = meetings[0].end;
		int countOfMeetings = 1;  //Select the first meeting by default

		//iterate for the rest of the meetings
		for (int i = 1; i < meetings.size(); i++) {
			if(meetings[i].start > lastEnd) {
				lastEnd = meetings[i].end;
				countOfMeetings++;
			}
		}

		return countOfMeetings;
	}
};

int main()
{
	Solution obj;
	vector<int> start = { 1, 3, 0, 5, 8, 5 };
	vector<int> end = { 2, 4, 6, 7, 9, 9 };
	cout << obj.maxMeetings(start, end) << endl;

	start = { 10, 12, 20 };
	end = { 20, 25, 30 };
	cout << obj.maxMeetings(start, end) << endl;


	start = { 1,    2 };
	end = { 100, 99 };
	cout << obj.maxMeetings(start, end) << endl;

	return 0;
}