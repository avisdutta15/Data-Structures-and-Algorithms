#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Fruit Into Baskets (LeetCode 904)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    You are visiting a farm with a row of fruit trees. Each tree has a type of fruit
    represented by fruits[i]. You have TWO baskets, and each basket can hold only
    ONE type of fruit (unlimited quantity of that type).

    Starting from any tree, you pick exactly one fruit from every tree moving to
    the right, stopping when you encounter a 3rd type of fruit (or reach the end).

    Return the MAXIMUM number of fruits you can pick.

    Translation: Find the longest subarray with at most 2 distinct elements.

    Examples:
    ---------
    Input:  fruits = [1, 2, 1]
    Output: 3
    Explanation: Pick all 3. Only 2 types (1 and 2).

    Input:  fruits = [0, 1, 2, 2]
    Output: 3
    Explanation: [1, 2, 2] — 2 types, length 3.

    Input:  fruits = [1, 2, 3, 2, 2]
    Output: 4
    Explanation: [2, 3, 2, 2] — 2 types, length 4.

    Constraints:
    ------------
    - 1 <= fruits.length <= 10^5
    - 0 <= fruits[i] < fruits.length

    Approach:
    ---------
    Variable Sliding Window — Find LONGEST valid window.

    Window condition: at most 2 distinct fruit types in the window.
    Invalid when: more than 2 distinct types.

    Track distinct types using a frequency map (type → count in window).
    - Expand: increment freq[fruits[right]].
    - If map size > 2 → INVALID → shrink from left.
    - Shrink: decrement freq[fruits[left]]. If count becomes 0, erase from map.
    - Update answer when window is valid.

    This is the same pattern as "Longest Substring with At Most K Distinct Characters"
    with K = 2.

    Worked Example:
    ---------------
    fruits = [1, 2, 3, 2, 2]

    left=0, right=0: freq={1:1}. distinct=1. result=1.
    left=0, right=1: freq={1:1, 2:1}. distinct=2. result=2.
    left=0, right=2: freq={1:1, 2:1, 3:1}. distinct=3 > 2! INVALID.
                     shrink: freq[1]-- → 0, erase 1. left=1. freq={2:1, 3:1}. distinct=2. VALID.
                     result=max(2, 2-1+1)=2.
    left=1, right=3: freq={2:2, 3:1}. distinct=2. result=max(2, 3)=3.
    left=1, right=4: freq={2:3, 3:1}. distinct=2. result=max(3, 4)=4.

    Result: 4 ✓ (subarray [2, 3, 2, 2])

    Time Complexity: O(N) — each element added/removed from map at most once
    Space Complexity: O(1) — map has at most 3 entries at any time
*/

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int left = 0, right = 0;
        int result = 0;
        unordered_map<int, int> freq;  // fruit type → count in window

        while (right < n) {
            // 1. EXPAND: add fruits[right] to window
            freq[fruits[right]]++;

            // 2. SHRINK: while window has more than 2 distinct types
            while (freq.size() > 2) {
                freq[fruits[left]]--;
                if (freq[fruits[left]] == 0)
                    freq.erase(fruits[left]);
                left++;
            }

            // 3. UPDATE: window is valid (at most 2 types)
            result = max(result, right - left + 1);

            right++;
        }

        return result;
    }
};

int main()
{
    Solution obj;

    vector<int> fruits1 = {1, 2, 1};
    cout << "Max fruits: " << obj.totalFruit(fruits1) << endl;  // 3

    vector<int> fruits2 = {0, 1, 2, 2};
    cout << "Max fruits: " << obj.totalFruit(fruits2) << endl;  // 3

    vector<int> fruits3 = {1, 2, 3, 2, 2};
    cout << "Max fruits: " << obj.totalFruit(fruits3) << endl;  // 4

    return 0;
}
