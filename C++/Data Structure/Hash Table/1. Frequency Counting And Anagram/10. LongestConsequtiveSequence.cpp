#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
	You must write an algorithm that runs in O(n) time.

	Examples:
	---------
	Example 1:
	Input: nums = [100,4,200,1,3,2]
	Output: 4
	Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
	
	Example 2:
	Input: nums = [0,3,7,2,5,8,4,6,0,1]
	Output: 9

	Example 3:
	Input: nums = [1,0,1,2]
	Output: 3

	Approach:
	---------
	1. Brute Force
		This is the most intuitive but inefficient approach. 
		It treats every number as a potential starting point and blindly searches the array 
		for the next numbers in the sequence.
		
		Logic: 
		Iterate through the array. 
		For every element x, perform a linear search to see if x+1 exists. 
			If yes, search for x+2, and so on.
		Time Complexity: O(N^3).
		Outer loop: N
		While loop: The sequence can be length N.
		linearSearch: Scans the array taking O(N).
		Total: O(N x N x N) = O(N^3).
		Space Complexity: O(1) (No extra data structures).
		Verdict: TLE (Time Limit Exceeded). Only works for very small arrays.

	2. (Sorting)
		This approach simplifies the problem by arranging the numbers in order. 
		Once sorted, consecutive numbers sit next to each other.
		
		Logic:
		Sort the array.
		Iterate once. 
			If current == previous, it's a duplicate (skip).
			If current == previous + 1, extend the current streak.
			Otherwise, the sequence is broken; reset streak to 1.
		Time Complexity: O(N x log N).
			Dominated by std::sort. The iteration is just O(N).
		Space Complexity: O(1) or O(log N) (depending on the sorting algorithm's stack usage).
		Verdict: Good but not optimal. It is very fast in practice but strictly slower than 
		the O(N) requirement. It also modifies the input array.

	3. (Hash Set with Erase)
		This approach optimizes the search to O(1) using a Hash Set and treats the set as a "pool of unvisited numbers."
		Logic:
			Load all numbers into a unordered_set.
			Iterate through the original vector nums.
			If a number exists in the set and is the start of a sequence (num-1 not present), begin counting.
		
			Critical Step: As you find num+1, num+2, etc., erase them from the set immediately. 
			This acts as a "visited" mark. If you encounter these numbers later in the main loop, 
			they won't be in the set, so they are skipped instantly.
		Time Complexity: O(N).
			Although there are nested loops, every element is added to the set once and erased/processed exactly once.
		Space Complexity: O(N) for the set.
		Verdict: Optimal O(N) Time. This fixes the TLE issue from your previous code by aggressively 
		erasing all members of the sequence found, ensuring no duplicate work is ever done.

	4. (Hash Set "Start Check")
		This is the standard "Best Practice" solution found in interviews. It iterates over the 
		Set rather than the array to handle duplicates implicitly and uses a "smart look-behind" check.
		Logic:
			Load all numbers into a unordered_set.
			Iterate strictly over the Set (automatically handles duplicates).
			The Filter: For every number x, check if x-1 exists.
				If x-1 exists: Then x is not the start of a sequence (it's the middle or end). Do nothing.
				If x-1 does NOT exist: Then x IS the start. Enter the while loop to count x+1, x+2...
		Time Complexity: O(N).
			We visit each number once during set creation.
			Inside the loop, the while loop runs only for sequence starts. In total, 
			the inner loop runs exactly N times across the entire execution (each number is counted 
			as part of a sequence exactly once).
		Space Complexity: O(N).
		Verdict: Cleanest Optimal Solution. It avoids modifying the set during iteration (no erase) 
		and has cleaner logic than approach #3.
*/

class Solution {
private:
	bool linearSearch(vector<int>& nums, int k) {
		for (auto i : nums) {
			if (i == k)
				return true;
		}
		return false;
	}
public:
	// for every A[i] check if can form A[i]+1....A[i]+n-2 from the array
	int longestConsecutiveNaive(vector<int>& nums) {
		int n = nums.size();

		int maxLength = 0;
		for (int i = 0; i < n; i++) {
			int consequtiveLength = 1;
			int nextNumber = nums[i] + 1;
			while (linearSearch(nums, nextNumber) == true) {
				consequtiveLength++;
				nextNumber++;
			}
			maxLength = max(maxLength, consequtiveLength);
		}
		return maxLength;
	}

	// sort the array then check the consequtive length till beginnig for every A[i] (check left side)
	int longestConsequtiveBetter(vector<int>& nums) {
		int n = nums.size();

		int maxLength = 0;
		int consequtiveLength = 1;
		sort(nums.begin(), nums.end());

		for (int i = 1; i < n; i++) {
			// skip the duplicates
			if (nums[i] == nums[i - 1]) {
				continue;
			}
			// if the previous element was a consequtive then increase length
			else if (nums[i] == nums[i - 1] + 1) {
				consequtiveLength++;
				maxLength = max(maxLength, consequtiveLength);
			}
			// if previous element was not a consequtive then dont increase length.
			// reset the length
			else if (nums[i] > nums[i - 1]) {
				consequtiveLength = 1;
			}
		}
		return maxLength;
	}

	// for every element A[i] check if this is the start of the sequence? (A[i-1] is not present in the hash)
	// if it is the start then check for all consequtive in the hashmap.
	// for array like [2, 1, 1, 3]
	// we would skip 2 as this is not the start of the sequence
	// we would take 1 and start the sequence count. [1, 2, 3]
	// we would again take 1 and start the sequence count [1, 2, 3]
	// so an observation, if the array has multiple same start element of the sequence, we do repetative work.
	// so delete the start element from the set once we use it so that duplicate sequences are not processed.
	// we also delete the other elements of the sequence from the hashset as they cannot be the start element
	// for any sequence in future. [1, 2, 3] for 1, we delete 2 and 3 after processing them as they cannot 
	// be the start of the sequence.
	int longestConsecutiveOptimized1(vector<int>& nums) {

		int n = nums.size();
		int maxLength = 0;
		unordered_set<int> hashSet(nums.begin(), nums.end());

		for (int i = 0; i < n; i++) {
			int consequtiveLength = 1;

			if (hashSet.find(nums[i])!=hashSet.end() && hashSet.find(nums[i] - 1) == hashSet.end()) {
				int nextNumber = nums[i] + 1;
				hashSet.erase(nums[i]);
				while (hashSet.find(nextNumber) != hashSet.end()) {
					consequtiveLength++;
					hashSet.erase(nextNumber);
					nextNumber++;
				}
			}
			maxLength = max(maxLength, consequtiveLength);
		}
		return maxLength;
	}

	// instead of iterating over the original array,
	// if the array has duplicate start elements we take care by deleting them.
	// but for the other duplicate elements e.g. [1, 2, 2, 3] 2 in this case,
	// we check for its presence in set.
	// So we can avoid all these by just iterating the set
	// and not the array. This ensures we are iterating uniques by checking if that
	// can be a start of the sequence or not.
	int longestConsecutiveOptimized2(vector<int>& nums) {

		int n = nums.size();
		int maxLength = 0;
		unordered_set<int> hashSet(nums.begin(), nums.end());

		for (auto i : hashSet) {
			int consequtiveLength = 1;
			if (hashSet.find(i - 1) == hashSet.end()) {
				int nextNumber = i + 1;
				while (hashSet.find(nextNumber) != hashSet.end()) {
					consequtiveLength++;
					nextNumber++;
				}
			}
			maxLength = max(maxLength, consequtiveLength);
		}
		return maxLength;
	}

};

int main() {
	Solution obj;
	vector<int> A = { 100,4,200,1,3,1,1,1,2,2,2 };
	cout << obj.longestConsecutiveOptimized2(A) << endl;

	return 0;
}