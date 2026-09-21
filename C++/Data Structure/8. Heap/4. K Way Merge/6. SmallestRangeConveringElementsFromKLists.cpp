#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

/*
    https://www.youtube.com/watch?v=HskhlSSie1g
    Problem Statement:
    ------------------
    LeetCode 632 - Smallest Range Covering Elements from K Lists

    You have k lists of sorted integers in non-decreasing order.
    Find the smallest range [a, b] that includes at least one number
    from each of the k lists.

    The range [a, b] is smaller than [c, d] if b - a < d - c,
    or if b - a == d - c and a < c.

    Examples:
    ---------

    Example 1:
        Input:  nums = [[4,10,15,24,26],
                        [0,9,12,20],
                        [5,18,22,30]]
        Output: [20, 24]
        Explanation:
            List 0 has 24, list 1 has 20, list 2 has 22.
            Range [20, 24] covers all three lists.
            No smaller range covers all three.

    Example 2:
        Input:  nums = [[1,2,3],
                        [1,2,3],
                        [1,2,3]]
        Output: [1, 1]
        Explanation:
            All lists have 1. Range [1,1] (size 0) covers all.

    Constraints:
    ------------
    - nums.length == k
    - 1 <= k <= 3500
    - 1 <= nums[i].length <= 50
    - -10^5 <= nums[i][j] <= 10^5
    - nums[i] is sorted in non-decreasing order.

    Approach: Min-Heap (K-way Merge)
    ---------------------------------
    The idea:
    1. We need one element from each list. 
    2. The range = max(chosen) - min(chosen). 
    3. To minimize the range, we want the chosen elements as close together as possible.
    4. Start with the first element of each list. These give us one element from every list. 
    The range is [min, max] of these k elements.
    5. Now, to try to shrink the range: 
        the only way to increase the minimum is to advance the list that has the current minimum. 
        Replace it with the next element from that list. Update the range.

    Why advance the minimum? 
    Since the lists are sorted in ascending order,
    - Advancing the maximum would only make the range bigger. 
    Advancing the minimum: the new value is >= old minimum. The min might increase, shrinking the range from the left side.
    - Advancing the minimum might bring it closer to the max, shrinking the range.
    Advancing the maximum: the new value is >= old maximum. The max can only increase or stay the same. 
    The range gets bigger or stays the same. Never helps.


    A min-heap gives us the current minimum in O(1). We track the current maximum separately.

    The heap always has exactly K elements — one per list. That's the invariant.
    That's why we break when any list is exhausted — we can't push a replacement, 
    so we'd drop below K elements. That means one list has no representative in the heap, 
    and we can't guarantee the range covers all K lists anymore.

    Time Complexity : O(N log K)
*/

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int rows = nums.size();

        // Min heap of {value, row, col}}
        priority_queue<tuple<int,int,int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        int current_max = INT_MIN;
        int ans_lo = 0;
        int ans_hi = INT_MAX;

        // Push first element of each list
        for (int row = 0; row < rows; row++) {
            pq.push({nums[row][0], row, 0});
            current_max = max(current_max, nums[row][0]);
        }

        while (!pq.empty()) {
            auto [current_min, row, col] = pq.top();
            pq.pop();

            // Update answer if current range is smaller
            if(current_max - current_min < ans_hi - ans_lo) {
                ans_lo = current_min;
                ans_hi = current_max;
            }

            // Advance the list that had the minimum
            if (col + 1 < nums[row].size()) {
                int next_element = nums[row][col+1];
                current_max = max(current_max, next_element);   // update max if the new element is larger
                pq.push({next_element, row, col+1});
            }
            else {
                break;  // this list is exhausted — can't maintain coverage
            }
        }

        return { ans_lo, ans_hi };
    }
};

int main() {
    Solution obj;
    vector<vector<int>> input = {{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}};
    vector<int> res = obj.smallestRange(input);
    cout << res[0] << " " << res[1] << endl;

    input = {{1,2,3}, {1,2,3}, {1,2,3}};
    res = obj.smallestRange(input);
    cout << res[0] << " " << res[1] << endl;
    return 0;
}