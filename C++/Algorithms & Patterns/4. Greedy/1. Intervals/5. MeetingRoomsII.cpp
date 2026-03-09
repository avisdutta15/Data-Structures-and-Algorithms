#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of meeting time interval objects consisting of start and end times [[start_1,end_1],[start_2,end_2],...] 
	(start_i < end_i), find the minimum number of rooms required to schedule all meetings without any conflicts.
	
	Note: (0,8),(8,10) is NOT considered a conflict at 8.

	Examples:
	---------
	Input: intervals = [(0,40),(5,10),(15,20)]
	Output: 2

	Explanation:
	day1: (0,40)
	day2: (5,10),(15,20)

	Approach 1 : Brute Force
	-------------------------
	The idea is to iterate through each train and for that train, check how many other trains have overlapping timings with it 
	- where current train's arrival time falls between the other train's arrival and departure times. 
	
	We keep track of this count for each train and continuously update our answer with the maximum count found.
		Train i overlaps with Train j arrives IF:
		It arrived after or at the exact same time as Train j (arr[j] <= arr[i])
		AND Train j departs after or at the exact same time Train i arrives (arr[i] <= dep[j])
	
	Time Complexity : O(n^2),
	Space Complexity : O(1)

	Approach 2: Better
	------------------
	The idea is to consider all events in sorted order. Once we have all events
	in sorted order, we can trace the number of trains at any time keeping track 
	of trains that have arrived, but not departed.

	Time	Event Type		Total Platforms Needed at this Time 
	9:00	Arrival			1
	9:10	Departure		0
	9:40	Arrival			1
	9:50	Arrival			2
	11:00	Arrival			3 
	11:20	Departure		2
	11:30	Departure		1
	12:00	Departure		0
	15:00	Arrival			1
	18:00	Arrival			2 
	19:00	Departure		1
	20:00	Departure		0

	Therefor minimum platforms needed = 3.

	Time Complexity : O(nlogn)
	Space Complexity: O(n)

	Approach 3: Best
	----------------
	Similar to Approach 2. But instead of creating an event array, we sort the arrival and departure array separately.
	And use the merge process of merge sort (2 pointers to pick the smallest event and process it).
			// Arrival happens before the next departure
			if (arr[i] < dep[j]) {
				numberOfPlatforms++;
				i++;
			}
			// Departure happens before the next arrival
			else if (arr[i] > dep[j]) {
				numberOfPlatforms--;
				j++;
			}
			else if (arr[i] == dep[j]) {
				// Collision: Train A arrives at the EXACT SAME MINUTE Train B departs.
				// Standard rule: We need 2 platforms for that specific minute.
				// Therefore, we MUST process the arrival first.
				numberOfPlatforms++;
				i++;
				// Notice we DO NOT increment j here! 
				// We leave the departure to be processed on the next loop iteration.
			}

	Time Complexity : O(nlogn)
	Space Complexity: O(1)
*/

class Interval {
public:
	int start, end;
	Interval(int start, int end) {
		this->start = start;
		this->end = end;
	}
};

class Solution1 {
public:
	int minMeetingRooms(vector<Interval>& intervals) {
		int rooms = 0, maxRoomsNeeded = 0;
		for (int i = 0; i < intervals.size(); i++) {
			rooms = 1;
			for (int j = 0; j < intervals.size(); j++) {
				if (j != i && intervals[i].start >= intervals[j].start && intervals[i].start < intervals[j].end) {
					rooms++;
				}
			}
			maxRoomsNeeded = max(rooms, maxRoomsNeeded);
		}
		return maxRoomsNeeded;
	}
};

class Solution2 {
public:
	int minMeetingRooms(vector<Interval>& intervals) {
		vector<pair<int, char>> meetings;

		for (auto i : intervals) {
			meetings.push_back({ i.start, 'S' });
			meetings.push_back({ i.end, 'E' });
		}

		sort(meetings.begin(), meetings.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
			//if the start times are equal, we want the 'E' to come before 'S' 
			//This is important because if a meeting starts at 11:00 and another meeting ends at 11:00,
			//we want to end the meeting and start a new meeting.
			if (a.first == b.first) {
				if (a.second == 'S' && b.second == 'E')
					return false;
				if (a.second == 'E' && b.second == 'S')
					return true;
			}
			return a.first < b.first;
		});

		int rooms = 0, maxRoomsNeeded = 0;
		for (auto i : meetings) {
			if (i.second == 'S') rooms++;
			else if (i.second == 'E') rooms--;
			maxRoomsNeeded = max(rooms, maxRoomsNeeded);
		}

		return maxRoomsNeeded;
	}
};

class Solution3 {
public:
	int minMeetingRooms(vector<Interval>& intervals) {
		vector<int> startTimes, endTimes;
		for (auto i : intervals) {
			startTimes.push_back(i.start);
			endTimes.push_back(i.end);
		}

		sort(startTimes.begin(), startTimes.end());
		sort(endTimes.begin(), endTimes.end());

		int i = 0, j = 0, meetingRooms = 0, maxRoomsNeeded = 0;
		while (i < startTimes.size() && j < endTimes.size()) {
			if (startTimes[i] < endTimes[j]) {
				meetingRooms++;
				i++;
			}
			else if (endTimes[j] < startTimes[i]) {
				meetingRooms--;
				j++;
			}
			else if (startTimes[i] == endTimes[j]) {
				meetingRooms--;
				j++;
			}

			maxRoomsNeeded = max(meetingRooms, maxRoomsNeeded);
		}
		return maxRoomsNeeded;
	}
};
int main()
{
	Solution1 obj1;
	vector<int> arr = { 1000, 935, 1100 };
	vector<int> dep = { 1200, 1240, 1130 };
	auto result = obj1.minPlatform(arr, dep);

	cout << result << endl;

	arr = { 900, 1235, 1100 };
	dep = { 1000, 1240, 1200 };
	result = obj1.minPlatform(arr, dep);

	cout << result << endl;

	return 0;
}