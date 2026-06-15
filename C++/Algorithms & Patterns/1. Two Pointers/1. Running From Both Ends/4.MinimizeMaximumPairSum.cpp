#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem Statement:
    ------------------
    The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the 
    largest pair sum in a list of pairs.

        - For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would 
        be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
    Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:

        - Each element of nums is in exactly one pair, and
        - The maximum pair sum is minimized.

    Return the minimized maximum pair sum after optimally pairing up the elements.

    Examples:
    --------
    Input: nums = [3,5,2,3]
    Output: 7
    Explanation: The elements can be paired up into pairs (3,3) and (5,2).
    The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.

    Input: nums = [3,5,4,2,4,6]
    Output: 8
    Explanation: The elements can be paired up into pairs (3,5), (4,4), and (6,2).
    The maximum pair sum is max(3+5, 4+4, 6+2) = max(8, 8, 8) = 8.

    Constraints:
    ------------
    
    Approach:
    ----------
    One might think of pairing up the smaller integers together so that the pair sum 
    is minimized at the beginning. However, in this way, we will end up pairing the 
    bigger integers together and hence will increase the maximum pair sum. For example, 
    we can pair up the array [1, 1, 2, 3] as (1, 1), (2, 3) with maximum sum as 5. 
    However, the optimal way would be to make a pair like (1, 3), (1, 2) with a maximum sum of 4. 
    
    This suggests that pairing adjacent numbers by value may not be the optimal approach.

    Observing the above example we can think about another potential strategy to pair up the 
    smallest integer with the greatest integer and then second-smallest with the second-greatest 
    and so on.

    1. Sort the array.
    2. Pair smallest with largest, second smallest with second largest and so on.
    3. Keep track of maximum sum of all such pairs.
*/

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        int maxSum = INT_MIN;

        while (l < r) {
            int pairSum = nums[l] + nums[r];
            maxSum = max(maxSum, pairSum);
            l++; r--;
        }
        return maxSum;
    }
};

int main()
{
    Solution obj;
    vector<int> A = { 3,5,2,3 };
    cout << obj.minPairSum(A) <<endl;

    return 0;
}