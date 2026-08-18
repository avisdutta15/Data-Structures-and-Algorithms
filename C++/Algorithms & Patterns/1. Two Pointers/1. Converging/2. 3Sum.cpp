#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem Statement:
    ------------------
    Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
    such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

    Notice that the solution set must not contain duplicate triplets.

    Examples:
    --------
    Input: nums = [-1,0,1,2,-1,-4]
    Output: [[-1,-1,2],[-1,0,1]]
    Explanation: 
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
    The distinct triplets are [-1,0,1] and [-1,-1,2].
    Notice that the order of the output and the order of the triplets does not matter.

    Input: nums = [0,1,1]
    Output: []
    Explanation: The only possible triplet does not sum up to 0.

    Input: nums = [0,0,0]
    Output: [[0,0,0]]
    Explanation: The only possible triplet sums up to 0.

    Constraints:
    ------------
    3 <= nums.length <= 3000
    -10^5 <= nums[i] <= 10^5

    Approach:
    ----------
    - Sort the array first
    - Fix the first element, and use two pointers approach to find the other two elements
    - Skip duplicates at each step to avoid duplicate triplets.
    -    How to skip duplicates?
    -        We are standing at i. Ask have we seen this element before? If yes, that means we have
    -        already processed for this element. So skip it.
    -        [-2, -2, 1, 1, 0, 0]
    -          i      j        k
    -        Now we need to move j and k
    -        [-2, -2, 1, 1, 0, 0]
    -          i         j  k
    -        Should we process this j and k? No, because A[j] == A[j-1] and we have already 
    -        processed A[j-1] so processing A[j] will yield a duplicate result. Hence we move j i.e. j++
    -        Similarly for k. Since A[k] == A[k+1] and we have already processed A[k+1], so processing
    -        it will yield a duplicate result. Hence we move k. i.e. k--
    -        We will follow the same thing for i.

    Time Complexity - 
        Sorting - O(NlogN)
              +
        for loop - O(N)
              X
        while loop - O(N)
        = O(NlogN) + O(N^2)
        
    Space Complexity - O(1)
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.size() == 0) return ans;

        sort(nums.begin(), nums.end());

        for (int i = 0; i <= nums.size() - 3; i++) {
            //skip duplicates for i
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int j = i + 1, k = nums.size() - 1;
            int sum = 0;

            while (j < k) {
                //skip duplicates for j
                if (j != i + 1 && nums[j] == nums[j - 1]) {
                    j++;
                }
                //skip duplicates for k
                else if (k != nums.size() - 1 && nums[k] == nums[k + 1]) {
                    k--;
                }
                //normal case
                else {
                    sum = nums[i] + nums[j] + nums[k];
                    if (sum == 0) {
                        ans.push_back({ nums[i], nums[j], nums[k] });
                        // move both pointers to search for other triplets
                        j++; k--;
                    }
                    else if (sum < 0)
                        j++;
                    else
                        k--;
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution obj;
    vector<int> A = { 1,2,0,1,0,0,0,0 };
    auto ans = obj.threeSum(A);
    for (auto v : ans) {
        for (auto i : v)
            cout << i << " ";
        cout << endl;
    }
}
