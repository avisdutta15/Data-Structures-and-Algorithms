#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an array people where people[i] is the weight of the ith person,
	and an infinite number of boats where each boat can carry a maximum weight of limit.

	Each boat carries at most two people at the same time, provided the sum of the
	weight of those people is at most limit.

	Return the minimum number of boats to carry every given person.

	Examples:
	---------
	Input: people = [1,2], limit = 3
	Output: 1
	Explanation: 1 boat (1, 2)

	Input: people = [3,2,2,1], limit = 3
	Output: 3
	Explanation: 3 boats (1, 2), (2) and (3)

	Input: people = [3,5,3,4], limit = 5
	Output: 4
	Explanation: 4 boats (3), (3), (4), (5)

	Constraints:
	------------
		1 <= people.length <= 5 * 10^4
		1 <= people[i] <= limit <= 3 * 10^4


	Approach 1 : Using LCS
	-----------------------
	The heaviest person is always the hardest to place in a boat.

	To minimize the number of boats, we should try pairing the heaviest
	remaining person with the lightest remaining person.
		- If they fit together, send them in one boat.
		- Otherwise, the heaviest person must go alone because they cannot pair with anyone else.

	Sorting allows us to make this greedy decision efficiently using two pointers.
*/

class Solution {
public:
	int numRescueBoats(vector<int>& people, int limit) {
		sort(people.begin(), people.end());
		int l = 0, r = people.size() - 1, boatCount = 0;
		while (l <= r) {
			if (people[l] + people[r] <= limit) {
				//these two people will go in 1 boat
				boatCount++; l++; r--;
			}
			else {
				//the heavier person will need 1 boat
				boatCount++; r--;
			}
		}
		return boatCount;
	}
};

int main() {
	Solution obj;
	vector<int> people = { 1,2 };
	int limit = 3;
	cout << obj.numRescueBoats(people, limit) << endl;


	people = { 3, 2, 2, 1 };
	limit = 3;
	cout << obj.numRescueBoats(people, limit) << endl;

	return 0;
}
