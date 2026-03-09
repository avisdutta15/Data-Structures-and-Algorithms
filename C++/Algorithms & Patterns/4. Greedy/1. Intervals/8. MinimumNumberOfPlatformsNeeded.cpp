#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given two arrays arr[] and dep[], that represent the arrival and departure time of i-th train respectively. 
	Find the minimum number of platforms required so that no train has to wait. If the departure time of one train 
	is the same as the arrival time of another train, both trains cannot use the same platform at that time.

	Examples:
	---------
	Input:	arr[] = [1000, 935,  1100], 
			dep[] = [1200, 1240, 1130]
	Output: 3
	Explanation: 

	
	Input: arr[] = [900, 1235, 1100], 
		   dep[] = [1000, 1240, 1200]
	Output: 1
	Explanation: Only 1 platform is required for all the three trains because the departure time of each train is less then arrival time of next train.


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

class Solution1 {
public:
	int minPlatform(vector<int>& arr, vector<int>& dep) {
		int numberOfPlatforms = 0;
		int maximumNumberOfPlatforms = 0;	//tracks the number of platforms needed at peek time.

		//for each train i check if it's schedule overlaps with any other train's schedule
		for (int i = 0; i < arr.size(); i++) {
			//1 platform is needed for the ith train to arrive
			numberOfPlatforms = 1;

			//check overlapping schedule with any other train's schedule. if yes then we need another platform.
			for (int j = 0; j < arr.size(); j++) {
				// Train i overlaps with Train j arrives IF:
				// It arrived after or at the exact same time as Train j (arr[j] <= arr[i])
				// AND Train j departs after or at the exact same time Train i arrives (arr[i] <= dep[j])
				if(i!=j && arr[j] <= arr[i] && arr[i] <= dep[j])
					numberOfPlatforms++;
			}

			//check how many platforms are needed at peak time.
			maximumNumberOfPlatforms = max(numberOfPlatforms, maximumNumberOfPlatforms);
		}

		return maximumNumberOfPlatforms;
	}
};

class Solution2 {
public:
	int minPlatform(vector<int>& arr, vector<int>& dep) {
		vector<pair<int, char>> trainSchedule;	//<time, 'a'/'d'> a->arrival, d->departure

		for (int time : arr) {
			trainSchedule.push_back({ time, 'A' });
		}

		for (int time : dep) {
			trainSchedule.push_back({ time, 'D' });
		}

		sort(trainSchedule.begin(), trainSchedule.end(), [](pair<int, char>& t1, pair<int, char>& t2) {
			// If times are exactly the same, process arrival ('A') before departure ('D')
			if (t1.first == t2.first) {
				if (t1.second == 'A' && t2.second == 'D')
					return true;
				if (t1.second == 'D' && t2.second == 'A')
					return false;
			}
			// Otherwise, sort strictly by time
			return t1.first < t2.first;
			});

		int platformNeeded = 0, maxPlatformNeeded = 0;
		for (auto& i : trainSchedule) {
			if (i.second == 'A')
				platformNeeded++;
			else
				platformNeeded--;
			maxPlatformNeeded = max(maxPlatformNeeded, platformNeeded);
		}

		return maxPlatformNeeded;
	}
};

class Solution3 {
public:
	int minPlatform(vector<int>& arr, vector<int>& dep) {
		sort(arr.begin(), arr.end());
		sort(dep.begin(), dep.end());

		int i = 0, j = 0;
		int numberOfPlatforms = 0, maximumNumberOfPlatforms = 0;

		while (i < arr.size() && j < dep.size()) {
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

			maximumNumberOfPlatforms = max(numberOfPlatforms, maximumNumberOfPlatforms);
		}
	
		return maximumNumberOfPlatforms;
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