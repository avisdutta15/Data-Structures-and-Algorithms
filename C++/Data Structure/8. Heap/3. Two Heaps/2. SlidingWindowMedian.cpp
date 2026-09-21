#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 480 - Sliding Window Median

    Given an array `nums` and an integer `k`, there is a sliding window
    of size `k` moving from left to right. For each window position,
    return the median of the k elements in the window.

    The median is the middle value in sorted order. If k is even,
    the median is the average of the two middle values.

    Examples:
    ---------

    Example 1:
        Input:  nums = [1,3,-1,-3,5,3,6,7], k = 3
        Output: [1.0, -1.0, -1.0, 3.0, 5.0, 6.0]
        Explanation:
            Window          Sorted          Median
            [1, 3, -1]     [-1, 1, 3]      1
            [3, -1, -3]    [-3, -1, 3]     -1
            [-1, -3, 5]    [-3, -1, 5]     -1
            [-3, 5, 3]     [-3, 3, 5]      3
            [5, 3, 6]      [3, 5, 6]       5
            [3, 6, 7]      [3, 6, 7]       6

    Example 2:
        Input:  nums = [1,2,3,4,2,3,1,4,2], k = 3
        Output: [2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0]

    Constraints:
    ------------
    - 1 <= k <= nums.length <= 10^5
    - -2^31 <= nums[i] <= 2^31 - 1

    Approach: Two Multisets (lo + hi) — like Median from Data Stream,
              but with removal support for the sliding window.
    ----------------------------------------------------------------

    Same idea as LC 295 (Find Median from Data Stream):
        lo (left half)  = smaller elements (acts like max-heap)
        hi (right half) = larger elements  (acts like min-heap)

    But unlike LC 295, this problem has a SLIDING WINDOW — the oldest
    element must be removed when the window slides. Heaps can't remove
    from the middle, so we use multisets instead.

    Why is getMedian() different from LC 295?
    -------------------------------------------
    In LC 295, we used:
        (lo.top() + hi.top()) / 2.0

    Here, nums[i] can be up to 2^31 - 1. Adding two such values
    overflows a 32-bit int:
        INT_MAX + INT_MAX = overflow!

    To avoid this, we split the division BEFORE adding:
        (*lo.rbegin() / 2.0) + (*hi.begin() / 2.0)

    This computes each half as a double first, then adds — no
    integer overflow possible.

        LC 295:   (a + b) / 2.0      ← a+b can overflow int
        LC 480:   (a/2.0) + (b/2.0)  ← safe, no overflow

    Operations:
    -----------
    addNumber(num):    insert into lo or hi based on value, rebalance.
    removeNumber(num): find and erase from whichever set has it, rebalance.
    getMedian():       peek at lo's max and/or hi's min.
    rebalance():       ensure lo.size() == hi.size() or lo.size() == hi.size() + 1.

    Algorithm for each window position:
    ------------------------------------
    1. Add nums[i] to the window and into the correct multiset.
    2. If window reaches size k:
        a. Compute median and record it.
        b. Remove the oldest element (sliding out) from its multiset.

    Complexity Analysis:
    --------------------
    Time:  O(n log k) — n elements, each insert/remove is O(log k).
    Space: O(k) — two multisets hold at most k elements total.

*/


class Solution {
private:
    multiset<int> lo;   //max heap for left size
    multiset<int> hi;   // min heap for right side

    void rebalance(){
        if(lo.size() == hi.size())
            return;
        else if (lo.size() > hi.size() + 1){
            int element = *lo.rbegin();
            lo.erase(lo.find(element));
            hi.insert(element);
        }
        else if(hi.size() > lo.size()){
            int element = *hi.begin();
            hi.erase(hi.find(element));
            lo.insert(element);
        }
    }

    void addNumber(int num){
        if(lo.size() == 0 || num <= *lo.rbegin()){
            lo.insert(num);
        }else
            hi.insert(num);

        rebalance();
    }

    void removeNumber(int num){
        if(lo.find(num) != lo.end())    lo.erase(lo.find(num));
        else if(hi.find(num) != hi.end())   hi.erase(hi.find(num));

        rebalance();
    }

    double getMedian(){
        return (lo.size() == hi.size()) ? (double)((double)(*lo.rbegin() / 2.0) + (*hi.begin() / 2.0)) : (*lo.rbegin());
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        queue<int> window;
        vector<double> result;

        for(int i=0; i<n; i++){
            // 1. Add to window
            window.push(nums[i]);

            // 2. Add to heaps
            addNumber(nums[i]);

            // 3. Window size check
            if(window.size() < k){
                continue;
            }
            else if(window.size() == k){
                // 3.1. push the median of the current window
                result.push_back(getMedian());

                // 3.2. remove the oldest element in the window 
                //      to make it a valid window for the next iteration
                int element = window.front();
                window.pop();
                removeNumber(element);
            }
        }

        return result;
    }
};

int main() {
    Solution obj;

    // Example 1: nums = [1,3,-1,-3,5,3,6,7], k = 3
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<double> result1 = obj.medianSlidingWindow(nums1, 3);
    cout << "Example 1: ";
    for (double d : result1) cout << d << " ";
    cout << endl;
    // Expected: 1 -1 -1 3 5 6

    // Example 2: nums = [1,2,3,4,2,3,1,4,2], k = 3
    Solution obj2;
    vector<int> nums2 = {1, 2, 3, 4, 2, 3, 1, 4, 2};
    vector<double> result2 = obj2.medianSlidingWindow(nums2, 3);
    cout << "Example 2: ";
    for (double d : result2) cout << d << " ";
    cout << endl;
    // Expected: 2 3 3 3 2 3 2

    // Edge case: even k (average of two middle values)
    Solution obj3;
    vector<int> nums3 = {1, 4, 2, 3};
    vector<double> result3 = obj3.medianSlidingWindow(nums3, 4);
    cout << "Even k:    ";
    for (double d : result3) cout << d << " ";
    cout << endl;
    // Expected: 2.5  (sorted [1,2,3,4], median = (2+3)/2)

    return 0;
}