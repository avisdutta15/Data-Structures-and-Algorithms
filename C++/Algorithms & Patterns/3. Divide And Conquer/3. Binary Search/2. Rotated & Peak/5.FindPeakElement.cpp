#include <iostream>
#include <vector>

using namespace std;

/*
	https://www.youtube.com/watch?v=cXxmbemS6XM
	Problem Statement:
	-----------------
	A peak element is an element that is strictly greater than its neighbors.
	Given a 0-indexed integer array nums, find a peak element, and return its index. 
	If the array contains multiple peaks, return the index to any of the peaks.

	You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always 
	considered to be strictly greater than a neighbor that is outside the array.

	You must write an algorithm that runs in O(log n) time.

	Examples:
	--------
	Input: nums = [1,2,3,1]
	Output: 2
	Explanation: 3 is a peak element and your function should return the index number 2.

	Input: nums = [1,2,1,3,5,6,4]
	Output: 5
	Explanation: Your function can return either index number 1 where the peak element is 2, 
	or index number 5 where the peak element is 6.

	Constraints:
	------------
	1 <= nums.length <= 1000
	-2^31 <= nums[i] <= 2^31 - 1
	nums[i] != nums[i + 1] for all valid i.

	Approach:
	---------
	The core idea is to treat the array like a terrain map. By looking at the "slope" at any given mid point, 
	we can figure out which direction is guaranteed to have a peak. 
	
	Because what goes up must eventually come down (or hit the -INF boundary), there will always be a peak 
	in the direction of the upward slope.

	If the right neighbor is taller than us, we are climbing up a hill to the right. 
		Since the far right edge of the array drops off to -infty, if we keep going right, 
		we are mathematically guaranteed to hit a peak. So, we discard the left half.
	If the left neighbor is taller than us, we are sliding down a hill. 
		This means we just passed a peak (or are moving away from one). We turn around and move left, 
		toward the higher ground.
	If we land in a "valley" where both neighbors are taller, either direction works.
	
	Handling Edge Cases Upfront
	- The algorithm starts by taking care of the boundaries so we don't have to deal with them inside the loop:
	- Single Element: if(N == 1) -> A single element is automatically a peak.
	- Left Boundary: if(A[0] > A[1]) -> Since A[-1] is -infty, if A[0] is greater than its right neighbor, it is a peak.
	- Right Boundary: if(A[N-2] < A[N-1]) -> Since A[N] is -\infty, if the last element is greater than its 
					  left neighbor, it is a peak.
*/

//Linear Search
class Solution{
public:
	int findPeakElement(vector<int> &arr) {
	    int n = arr.size();

		if(n==1)
			return 0;
		if(arr[0]>arr[1])
			return 0;
		if(arr[n-1]>arr[n-2])
			return n-1;
		
	    for(int i = 1; i < n-1; i++) {
	    	bool left = true;
	        bool right = true;
	      
	        // Check for element to the left
	        if(arr[i] <= arr[i - 1]) 
	            left = false;
	      
	        // Check for element to the right
	        if(arr[i] <= arr[i + 1])
	            right = false;
	      
	        // If arr[i] is greater than its left as well as
	        // its right element, return its index
	        if(left && right) {
	        	return i;
	        }
	    }
	    return 0;
	}
};

// Binary Search
class Solution2 {
public:
	int findPeakElement(vector<int>& A) {
		int N = A.size();

		// Edge Case: If the array has only one element
		if(N == 1)
			return 0;

		// Edge Case: If the first element is peak
		if(A[0] > A[1])
			return 0;

		// Edge Case: If the last element is peak
		if (A[N - 2] < A[N - 1])
			return (N - 1);
		
		// General Case: Check for peak in the remaining array
		int left = 1, right = N - 2;
		int mid = 0;

		while (left <= right) {
			mid = left + (right - left) / 2;

			// Check if mid is peak
			if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1])
				return mid;

			// Check if we are in ascending order
			if(A[mid] < A[mid + 1])
				left = mid + 1;
			// Check if we are in descending order
			else if(A[mid-1] > A[mid])
				right = mid - 1;
		}

		return mid;
	}
};

int main() {
	Solution obj;
	vector<int> A = { 1,2,3,1 };
	vector<int> B = { 1,2,1,3,5,6,4 };
	vector<int> C = { 1 };

	cout << obj.findPeakElement(A) << endl;
	cout << obj.findPeakElement(B) << endl;
	cout << obj.findPeakElement(C) << endl;
}
