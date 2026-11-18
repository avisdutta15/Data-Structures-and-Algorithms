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
    https://www.youtube.com/watch?v=2MmGzdiKR9Y
    Problem Statement:
    -----------------
    Given an integer array nums, find the subarray with the largest sum, and return its sum.

    Examples:
    --------- 
    Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: The subarray [4,-1,2,1] has the largest sum 6.

    Input: nums = [1]
    Output: 1
    Explanation: The subarray [1] has the largest sum 1.

    Input: nums = [5,4,-1,7,8]
    Output: 23
    Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.

    Constraints:
    ------------
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4


    Approach: 
    --------
    At every index i, we have two choices:
    1. Add the element to the existing subarray
    2. Start a new subarray from the current element
    We choose the choice that gives us a larger sum at each step.
    Track the global maximum sum at every index i.

    Time Complexity: O(n)
    Space Complexity: O(1)

*/

// TC: O(N^2) SC: O(1)
class Solution1 {
public:
    int maxSubArray(vector<int>& nums) {
        int max_subarray_sum = INT_MIN;
        int current_subarray_sum = 0;

        for (int i = 0; i < nums.size(); i++) {
            current_subarray_sum = 0;

            // a new subarray starting at index i and ending at j
            for (int j = i; j < nums.size(); j++) {
                current_subarray_sum += nums[j];
                max_subarray_sum = max(max_subarray_sum, current_subarray_sum);
            }
        }

        return max_subarray_sum;
    }
};

// TC: O(N) SC: O(N)
class Solution2 {
public:
    int maxSubArray(vector<int>& nums) {

        // maximum_subarray_sum_ending_at[i] represents the maximum sum of a contiguous subarray ending at index i
        // This is not the global maximum, just the maximum ending at that index
        vector<int> maximum_subarray_sum_ending_at(nums.size());
        maximum_subarray_sum_ending_at[0] = nums[0];

        // global maximum sum
        int max_subarray_sum = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            // At index i, either extend the existing subarray or start a new one
            int subarray_sum_ending_at_i = maximum_subarray_sum_ending_at[i-1] + nums[i];
            int subarray_sum_starting_at_i = nums[i];

            maximum_subarray_sum_ending_at[i] = max(subarray_sum_ending_at_i, subarray_sum_starting_at_i);

            // Update the global maximum if the current running sum is larger
            max_subarray_sum = max(max_subarray_sum, maximum_subarray_sum_ending_at[i]);
        }

        return max_subarray_sum;
    }
};

// TC: O(N) SC: O(1)
class Solution3 {
public:
    int maxSubArray(vector<int>& nums) {

        // maximum_subarray_sum_ending_at_i represents the maximum sum of a contiguous subarray ending at index i
        // This is not the global maximum, just the maximum ending at that index
        int maximum_subarray_sum_ending_at_i = nums[0];

        // global maximum sum
        int max_subarray_sum = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            // At index i, either extend the existing subarray or start a new one
            int subarray_sum_ending_at_i = maximum_subarray_sum_ending_at_i + nums[i];
            int subarray_sum_starting_at_i = nums[i];

            maximum_subarray_sum_ending_at_i = max(subarray_sum_ending_at_i, subarray_sum_starting_at_i);

            // Update the global maximum if the current running sum is larger
            max_subarray_sum = max(max_subarray_sum, maximum_subarray_sum_ending_at_i);
        }

        return max_subarray_sum;
    }
};

// Print the start and end indices
class Solution4 {
public:
    int printMaxSubArray(vector<int>& nums) {

        // maximum_subarray_sum_ending_at_i represents the maximum sum of a contiguous subarray ending at index i
        // This is not the global maximum, just the maximum ending at that index
        int maximum_subarray_sum_ending_at_i = nums[0];

        // global maximum sum
        int max_subarray_sum = nums[0];

        int start_index = 0;
        int end_index = 0;


        for (int i = 1; i < nums.size(); i++)
        {
            // At index i, either extend the existing subarray or start a new one
            int subarray_sum_ending_at_i = maximum_subarray_sum_ending_at_i + nums[i];
            int subarray_sum_starting_at_i = nums[i];

            // Update start if we start from ith index.
            if (subarray_sum_starting_at_i > subarray_sum_ending_at_i) {
                start_index = i;
                maximum_subarray_sum_ending_at_i = subarray_sum_starting_at_i;
            }
            else {
                maximum_subarray_sum_ending_at_i = subarray_sum_ending_at_i;
            }

            // Update the global maximum if the current running sum is larger
            // Update the end index if we update the global max sum
            if (maximum_subarray_sum_ending_at_i > max_subarray_sum ) {
                end_index = i;
                max_subarray_sum = maximum_subarray_sum_ending_at_i;
            }
        }

        cout << "Start Index: " << start_index << ", End Index: " << end_index << endl;

        return max_subarray_sum;
    }
};


int main() {
    Solution1 obj1;
	vector<int> A = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << obj1.maxSubArray(A) << endl;

    Solution2 obj2;
    cout << obj2.maxSubArray(A) << endl;

    Solution3 obj3;
    cout << obj3.maxSubArray(A) << endl;

    Solution4 obj4;
    cout << obj4.printMaxSubArray(A) << endl;
	return 0;
}