#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
#include <limits>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an integer array nums consisting of n elements, and an integer k.

	Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value.
	Any answer with a calculation error less than 10-5 will be accepted.

	Examples:
	--------
	Example 1:
	Input: nums = [1,12,-5,-6,50,3], k = 4
	Output: 12.75000
	Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

	Example 2:
	Input: nums = [5], k = 1
	Output: 5.00000


	Approach:
	---------
	Sliding Window - Fixed Size
	Note : We dont need a INT_MIN style Double_MIN
	We can keep the first window avg as the max and the compare the rest of the arrays windows with this avg.
*/

class Solution {
public:
	double findMaxAverageType1(vector<int>& nums, int k) {
        int sum = 0, maxSum = 0;
        int start = 0, end = 0;

        // since we have -ve numbers, we cannot keep maxSum = 0
        // so we will keep the first window sum as maxSum. Track the
        // first window using a boolean variable
        bool firstWindow = false;

        while(end < nums.size()){
            sum = sum + nums[end];

            if(end - start + 1 < k)
                end++;
            else if(end - start + 1 == k){
                // process window
                if(firstWindow == false){
                    firstWindow = true;
                    maxSum = sum;
                }else
                    maxSum = max(maxSum, sum);

                // eliminate out of window elements
                sum = sum - nums[start];

                // slide the window
                start++;
                end++;
            }
        }
		
		// return the average
        return (double)maxSum / k;
    }

	double findMaxAverageType2(vector<int>& nums, int k) {
		double maxAverage = 0;
		int n = nums.size();
		double sum = 0;

		//process the first window
		for (int i = 0; i < k; i++) {
			sum += nums[i];
		}
		maxAverage = sum / k;

		//process rest of the array
		for (int i = k; i < n; i++) {
			sum = sum - nums[i - k];
			sum = sum + nums[i];
			maxAverage = max(maxAverage, sum / k);
		}
		return maxAverage;
	}
};

int main() {
	Solution obj;
	vector<int> nums = { 1,12,-5,-6,50,3 };
	cout << obj.findMaxAverageType1(nums, 4) << endl;

	nums = { -1 };
	cout << obj.findMaxAverageType1(nums, 1) << endl;

	return 0;
}