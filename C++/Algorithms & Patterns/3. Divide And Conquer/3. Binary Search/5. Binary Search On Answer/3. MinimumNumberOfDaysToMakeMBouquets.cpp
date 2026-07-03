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
	https://www.youtube.com/watch?v=n4F8Q5HV8RY
	Problem Statement:
	-----------------
	You are given an integer array bloomDay, an integer m and an integer k.
	You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.
	The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] 
	and then can be used in exactly one bouquet.
	Return the minimum number of days you need to wait to be able to make m bouquets from the garden. 
	If it is impossible to make m bouquets return -1.

 
	Examples:
	---------
	Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
	Output: 3
	Explanation: Let us see what happened in the first three days. x means flower bloomed 
				 and _ means flower did not bloom in the garden.
	We need 3 bouquets each should contain 1 flower.
	After day 1: [x, _, _, _, _]   // we can only make one bouquet.
	After day 2: [x, _, _, _, x]   // we can only make two bouquets.
	After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.

	Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
	Output: -1
	Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. 
	We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.

	Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
	Output: 12
	Explanation: We need 2 bouquets each should have 3 flowers.
	Here is the garden after the 7 and 12 days:
	After day 7: [x, x, x, x, _, x, x]
	We can make one bouquet of the first three flowers that bloomed. 
	We cannot make another bouquet from the last three flowers that bloomed 
	because they are not adjacent.
	After day 12: [x, x, x, x, x, x, x]
	It is obvious that we can make two bouquets in different ways.

	Constraints:
	------------

	Approach:
	--------
		canWeMakeMBouquetInIDays(int day, bloomDay[], int m, int k)
			bouquets = 0;
			flowersInEachBouquet = 0;
	
			for (int i = 0; i < bloomDay.size(); i++) {
				// if the flower can bloom within the given 'day' i.e. our minimum day
				// then we can include that flower in our bouquet
			
				if (bloomDay[i] <= day) {
					flowersInEachBouquet++;
					if (flowersInEachBouquet == k) {
						bouquets++;
						flowersInEachBouquet = 0;
					}
				}
				else {
					// non-blooming flower breaks the consecutive streak
					flowersInEachBouquet = 0;
				}
			}

			// if we have made at least m bouquets with k flowers in each bouquet
			// then return true else false
			return bouquets >= m;
		

		search space [minimumNumberOfDaysToBloomAFlower, maximumNumberOfDaysToBloomAFlower]


	Solution 1: Linear Scan to find the minimum number of days to make bouquets
		for day = minDay to maxDay          => O(maxDay - minDay) iterations
			canWeMake() scans all n flowers => O(n)
		
		T.C. = O((maxDay - minDay) * n)
		S.C. = O(1)

	Solution 2: Binary Search on Answer to find the minimum number of days to make bouquets
		binary search on [minDay, maxDay]   => O(log(maxDay - minDay)) iterations
			canWeMake() scans all n flowers => O(n)
	
		T.C. = O( log(maxDay - minDay) * n )
		S.C. = O(1)
*/

// Linear Search
class Solution1 {
private:
	bool canWeMakeMBouquetInIDays(int day, vector<int>& bloomDay, int m, int k) {
		int bouquets = 0;
		int flowersInEachBouquet = 0;

		for (int i = 0; i < bloomDay.size(); i++) {
			// if the flower can bloom within the given 'day' i.e. our minimum day
			// then we can include that flower in our bouquet
			if (bloomDay[i] <= day) {
				flowersInEachBouquet++;
				if (flowersInEachBouquet == k) {
					bouquets++;
					flowersInEachBouquet = 0;
				}
			}
			else {
				// non-blooming flower breaks the consecutive streak
				flowersInEachBouquet = 0;
			}
		}

		// if we have made at least m bouquets with k flowers in each bouquet
		// then return true else false
		return bouquets >= m;
	}

public:
	int minDays(vector<int>& bloomDay, int m, int k) {
		// Base Case: if number of bouquets and the 
		// number of flowers required in each bouquet is 
		// greater than the given number of flowers, then it is
		// not possible to make the bouquets.
		if (m * k > bloomDay.size())
			return -1;

		int minimumumNumberOfDaysToBloomAFlower = *min_element(bloomDay.begin(), bloomDay.end());
		int maximumNumberOfDaysToBloomAFlower = *max_element(bloomDay.begin(), bloomDay.end());


		int lo = minimumumNumberOfDaysToBloomAFlower;
		int hi = maximumNumberOfDaysToBloomAFlower;
		int mid = 0;
		int minimumNumberOfDaysToMakeMBouquets = -1;

		while (lo <= hi)
		{
			mid = lo + (hi - lo) / 2;
			if (canWeMakeMBouquetInIDays(mid, bloomDay, m, k) == true) {
				minimumNumberOfDaysToMakeMBouquets = mid;
				hi = mid - 1;			// minimize the number of days
			}
			else {
				lo = mid + 1;
			}
		}

		return minimumNumberOfDaysToMakeMBouquets;
	}
};


// Binary Search
class Solution2 {
private:
	bool canWeMakeMBouquetInIDays(int day, vector<int>& bloomDay, int m, int k) {
		int bouquets = 0;
		int flowersInEachBouquet = 0;

		for (int i = 0; i < bloomDay.size(); i++) {
			// if the flower can bloom within the given 'day' i.e. our minimum day
			// then we can include that flower in our bouquet
			if (bloomDay[i] <= day) {
				flowersInEachBouquet++;
				if (flowersInEachBouquet == k) {
					bouquets++;
					flowersInEachBouquet = 0;
				}
			}
			else {
				// non-blooming flower breaks the consecutive streak
				flowersInEachBouquet = 0;
			}
		}

		// if we have made at least m bouquets with k flowers in each bouquet
		// then return true else false
		return bouquets >= m;
	}

public:
	int minDays(vector<int>& bloomDay, int m, int k) {
		// Base Case: if number of bouquets and the 
		// number of flowers required in each bouquet is 
		// greater than the given number of flowers, then it is
		// not possible to make the bouquets.
		if (m * k > bloomDay.size())
			return -1;

		int minimumumNumberOfDaysToBloomAFlower = *min_element(bloomDay.begin(), bloomDay.end());
		int maximumNumberOfDaysToBloomAFlower = *max_element(bloomDay.begin(), bloomDay.end());


		int lo = minimumumNumberOfDaysToBloomAFlower;
		int hi = maximumNumberOfDaysToBloomAFlower;
		int mid = 0;
		int minimumNumberOfDaysToMakeMBouquets = -1;

		while(lo <= hi)
		{
			mid = lo + (hi - lo) / 2;
			if (canWeMakeMBouquetInIDays(mid, bloomDay, m, k) == true) {
				minimumNumberOfDaysToMakeMBouquets = mid;
				hi = mid - 1;			// minimize the number of days
			}
			else {
				lo = mid + 1;
			}
		}

		return minimumNumberOfDaysToMakeMBouquets;
	}
};


int main() {
	Solution1 obj;
	vector<int> bloomDay = { 1, 10, 3, 10, 2 };
	cout << obj.minDays(bloomDay, 3, 1) << endl;
	return 0;
}