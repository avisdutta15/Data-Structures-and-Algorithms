#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
	https://www.youtube.com/watch?v=zfcGwzfDNu0
	Problem Statement:
	-----------------
	There are some spherical balloons taped onto a flat wall that represents the XY-plane. 
	The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] 
	denotes a balloon whose horizontal diameter stretches between xstart and xend. 
	
	You do not know the exact y-coordinates of the balloons.
	Arrows can be shot up directly vertically (in the positive y-direction) from different points 
	along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. 
	
	There is no limit to the number of arrows that can be shot. 
	A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
	
	Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
	
	Examples:
	---------
	Input: points = [[10,16],[2,8],[1,6],[7,12]]
	Output: 2
	Explanation: The balloons can be burst by 2 arrows:
	- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
	- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

	Input: points = [[1,2],[3,4],[5,6],[7,8]]
	Output: 4
	Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.

	Input: points = [[1,2],[2,3],[3,4],[4,5]]
	Output: 2
	Explanation: The balloons can be burst by 2 arrows:
	- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
	- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].


	Constraints:
	------------
	
	Approach:
	--------
	Interval Merging.
		Sort on the basis of start points.
		When we merge the intervals, we need can use the same arrow.
		If we cannot merge, we need one more arrow.
*/

class Solution {
public:
	int findMinArrowShots(vector<vector<int>>& points) {
		int n = points.size();
		sort(begin(points), end(points));

		vector<int> prev = points[0];
		int arrows = 1;	// minimum 1 arrow is needed

		for (int i = 1; i < n; i++) {
			int currStartPoint = points[i][0];
			int currEndPoint = points[i][1];

			int prevStartPoint = prev[0];
			int prevEndPoint = prev[1];

			if (currStartPoint > prevEndPoint) { //no overlap
				// since the current and prev ballons are not overlapping, 
				// we need 1 more arrow to shoot current ballon.
				arrows++;	
				prev = points[i];
			}
			else {
				// overlap
				// since the ballons are overlapping, we can shoot both with same arrow
				prev[0] = max(prevStartPoint, currStartPoint);
				prev[1] = min(prevEndPoint, currEndPoint);
			}
		}

		return arrows;
	}
};

int main() {
	Solution obj;
	vector<vector<int>> points = { {1, 2},{2, 3},{3, 4},{4, 5} };
	cout << obj.findMinArrowShots(points) << endl;
	return 0;
}