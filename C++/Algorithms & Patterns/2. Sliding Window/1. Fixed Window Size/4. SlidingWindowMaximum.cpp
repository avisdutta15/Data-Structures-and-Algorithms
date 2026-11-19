#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an array of integers nums, there is a sliding window of size k which
	is moving from the very left of the array to the very right. You can only see the k
	numbers in the window. Each time the sliding window moves right by one position.

	Return the max sliding window.

	Examples:
	--------
	Example 1:
	Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
	Output: [3,3,5,5,6,7]
	Explanation:
	Window position                Max
	---------------               -----
	[1  3  -1] -3  5  3  6  7       3
	 1 [3  -1  -3] 5  3  6  7       3
	 1  3 [-1  -3  5] 3  6  7       5
	 1  3  -1 [-3  5  3] 6  7       5
	 1  3  -1  -3 [5  3  6] 7       6
	 1  3  -1  -3  5 [3  6  7]      7

	Example 2:
	Input: nums = [1], k = 1
	Output: [1]

	Constraints:
	1 <= nums.length <= 105
	-104 <= nums[i] <= 104
	1 <= k <= nums.length

	Approach:
	---------
	A brute force solution would check every window and find the max, but that would be too slow ( (O(n . k)) ).
	
	Instead, we can use a deque (double-ended queue) to efficiently maintain useful elements in the window.

	The key insight is:

		Keep the deque monotonic decreasing (values in decreasing order).
		This way, the front of the deque always contains the maximum of the current window.
	
	Steps:
	1. Iterate through the array indices i.
	2. Remove indices from the front if they are out of the current window (i - k).
	3. Remove indices from the back if their corresponding values are smaller than the current value 
	4. nums[i] (since they can never be max again).
	5. Push the current index i into the deque.
	6. Once we’ve processed at least k elements, the front of the deque is the max for this window, 
	   so push nums[dq.front()] into the result.

	T.C. - O(n)
	S.C. - O(k)
*/

class Solution {
public:
    vector<int> maxSlidingWindowType1(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> DQ;  //Q has indices
        int start = 0, end = 0;

        while (end < nums.size()) {
            // 1. Add the current element to window. Maintain decereasing monotonicity of the deque so that largest element always at front
            while (!DQ.empty() && nums[DQ.back()] < nums[end])
                DQ.pop_back();
            DQ.push_back(end);

            // 2.1. Check if the window size == K. If not then expand the pointer to right to add more element
            if (end - start + 1 < k)
                end++;
			// 2.2. If the window size == K.
            else if (end - start + 1 == k) {
                result.push_back(nums[DQ.front()]);			// 1. Process this window

                if(DQ.front() <= start)						// 2. Delete the starting element from window
                    DQ.pop_front();

                start++;									// 3. Adjust pointers to slide this window
                end++;
            }
        }
        return result;
    }

	vector<int> maxSlidingWindowType2(vector<int>& nums, int k) {
		if (nums.size() <= 1)
			return nums;

		int n = nums.size();
		vector<int> maxOfEachWindow;
		deque<int> Q;	//maintain a monotonically decreasing queue

		//process the first window
		for (int i = 0; i < k; i++) {
			while (!Q.empty() && nums[Q.back()] < nums[i]) {
				Q.pop_back();
			}
			Q.push_back(i);
		}

		if (!Q.empty())
			maxOfEachWindow.push_back(nums[Q.front()]);

		//process rest of the array
		for (int i = k; i < n; i++) {
			//delete the out of window elements from Q
			if (!Q.empty() && Q.front() == i - k) {
				Q.pop_front();
			}

			//insert the new element into Q maintaining the monotonic decreasing property
			while (!Q.empty() && nums[Q.back()] < nums[i]) {
				Q.pop_back();
			}
			Q.push_back(i);

			//insert into ans.
			if (!Q.empty())
				maxOfEachWindow.push_back(nums[Q.front()]);
		}
		return maxOfEachWindow;
	}
};

int main() {
	Solution obj;
	vector<int> nums = { 1,3,1,2,0,5 };
	auto maxOfEachWindow = obj.maxSlidingWindowType1(nums, 3);
	for (auto i : maxOfEachWindow) {
		cout << i << " ";
	}
	cout << endl;

	nums = { 1 };
	maxOfEachWindow = obj.maxSlidingWindow(nums, 3);
	for (auto i : maxOfEachWindow) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}
