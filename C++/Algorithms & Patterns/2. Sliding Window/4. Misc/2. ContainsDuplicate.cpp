#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

/*
    Problem (LC 217. Contains Duplicate)
    -------
    Given an integer array nums, return true if any value appears
    at least twice, and false if every element is distinct.

    Example: [1, 2, 3, 1] → true  (1 appears twice)
             [1, 2, 3, 4] → false (all distinct)

    Approach 1 — Brute Force [O(n²) time, O(1) space]
    =========================================================================
    For each element, check every element after it for a match.
    Simple but slow — two nested loops.

    Example: [1, 2, 3, 1]
        i=0, j=1: 1 vs 2 → no
        i=0, j=2: 1 vs 3 → no
        i=0, j=3: 1 vs 1 → MATCH! return true

    Approach 2 — Sort [O(n log n) time, O(1) space*]
    =========================================================================
    If the array is sorted, duplicates become adjacent.
    Sort first, then one pass checking neighbors.

    * O(1) extra space if we sort in-place (modifies input).

    Example: [1, 2, 3, 1]
        After sort: [1, 1, 2, 3]
                     ^  ^
                     adjacent match → return true

    Why this works:
        In a sorted array, equal elements are always next to each other.
        So checking adjacent pairs is sufficient — no need to compare
        every pair like the brute force.

    Approach 3 — Hash Set [O(n) time, O(n) space]
    =========================================================================
    Insert elements one by one into a hash set.
    Before inserting, check if it's already there → duplicate.

    The set gives O(1) average lookup, so the total is O(n).

    Trade-off: fastest approach, but uses O(n) extra space.

    Example: [1, 2, 3, 1]
        insert 1 → set = {1}
        insert 2 → set = {1, 2}
        insert 3 → set = {1, 2, 3}
        insert 1 → already in set! return true
*/

class Solution1 {
public:
    bool containsDuplicate(vector<int>& nums) {
        int N = static_cast<int>(nums.size());

        // Check every pair (i, j) where j > i
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                // If any two elements match → duplicate found
                if (nums[i] == nums[j]) return true;
            }
        }

        // No pair matched → all elements are distinct
        return false;
    }
};

class Solution2 {
public:
    bool containsDuplicate(vector<int>& nums) {
        int N = static_cast<int>(nums.size());

        // Sort in-place: O(n log n) time
        sort(nums.begin(), nums.end());

        // One pass: check if any adjacent elements are equal
        for (int i = 1; i < N; i++) {
            // In a sorted array, duplicates are always neighbors.
            // If nums[i] == nums[i-1], we found a duplicate.
            if (nums[i] == nums[i - 1]) return true;
        }

        // No adjacent match → all distinct
        return false;
    }
};

class Solution3 {
public:
    bool containsDuplicate(vector<int>& nums) {
        int N = static_cast<int>(nums.size());
        unordered_set<int> seen;

        for (int i = 0; i < N; i++) {
            // Check if this element was seen before.
            // count() returns 1 if present, 0 if not — O(1) average.
            if (seen.count(nums[i]) > 0) {
                // Already in the set → duplicate found
                return true;
            }

            // First time seeing this element → add it to the set
            seen.insert(nums[i]);
        }

        // Went through all elements without finding a duplicate
        return false;
    }
};

int main() {
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    // ---- Test 1: has duplicate ----
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "=== [1, 2, 3, 1] — has duplicate ===" << endl;
    cout << "Brute Force: " << boolalpha << s1.containsDuplicate(nums1) << " (expected true)" << endl;
    nums1 = {1, 2, 3, 1};  // reset (sort modifies input)
    cout << "Sort:        " << boolalpha << s2.containsDuplicate(nums1) << " (expected true)" << endl;
    nums1 = {1, 2, 3, 1};
    cout << "Hash Set:    " << boolalpha << s3.containsDuplicate(nums1) << " (expected true)" << endl;

    // ---- Test 2: all distinct ----
    vector<int> nums2 = {1, 2, 3, 4};
    cout << "\n=== [1, 2, 3, 4] — all distinct ===" << endl;
    cout << "Brute Force: " << boolalpha << s1.containsDuplicate(nums2) << " (expected false)" << endl;
    nums2 = {1, 2, 3, 4};
    cout << "Sort:        " << boolalpha << s2.containsDuplicate(nums2) << " (expected false)" << endl;
    nums2 = {1, 2, 3, 4};
    cout << "Hash Set:    " << boolalpha << s3.containsDuplicate(nums2) << " (expected false)" << endl;

    // ---- Test 3: duplicate at end ----
    vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    cout << "\n=== [1,1,1,3,3,4,3,2,4,2] — multiple duplicates ===" << endl;
    cout << "Brute Force: " << boolalpha << s1.containsDuplicate(nums3) << " (expected true)" << endl;
    nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    cout << "Sort:        " << boolalpha << s2.containsDuplicate(nums3) << " (expected true)" << endl;
    nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    cout << "Hash Set:    " << boolalpha << s3.containsDuplicate(nums3) << " (expected true)" << endl;

    // ---- Test 4: single element ----
    vector<int> nums4 = {7};
    cout << "\n=== [7] — single element ===" << endl;
    cout << "Hash Set:    " << boolalpha << s3.containsDuplicate(nums4) << " (expected false)" << endl;

    // ---- Test 5: empty ----
    vector<int> nums5 = {};
    cout << "\n=== [] — empty ===" << endl;
    cout << "Hash Set:    " << boolalpha << s3.containsDuplicate(nums5) << " (expected false)" << endl;

    return 0;
}
