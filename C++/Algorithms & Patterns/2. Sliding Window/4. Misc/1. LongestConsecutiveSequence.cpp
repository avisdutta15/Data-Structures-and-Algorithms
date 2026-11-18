#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
    https://www.youtube.com/watch?v=oO5uLE7EUlM
    
    Problem (LC 128. Longest Consecutive Sequence)
    -------
    Given an unsorted array of integers nums, return the length of the
    longest consecutive elements sequence. Must run in O(n) time.

    Example: [100, 4, 200, 1, 3, 2] → 4  (sequence [1, 2, 3, 4])

    =========================================================================
    Approach 1 — Iterate over ARRAY, check if start of sequence
    =========================================================================
    Problem: iterates over the ARRAY, not the SET.
    If nums has duplicates, the same sequence-start is processed
    multiple times, doing identical work each time.

    Example:  nums = [1, 1, 1, 2, 3]
        i=0: nums[0]=1, start? yes → walk 1→2→3, length=3
        i=1: nums[1]=1, start? yes → walk 1→2→3, length=3  ← redundant!
        i=2: nums[2]=1, start? yes → walk 1→2→3, length=3  ← redundant!

    Time:  O(n) amortized for unique elements, but duplicates cause
           redundant walks.
    Space: O(n)

    =========================================================================
    Approach 2 — Iterate over SET, check if start of sequence
    =========================================================================
    Same logic, one critical change: iterate over the HASH SET, not the array.

    The set contains only UNIQUE values. Each unique value is visited
    exactly once in the outer loop → no duplicate walks.

    Example:  nums = [5, 5, 5, 5, 5, 6, 7, 8, 9, 10]
        Approach 1 (array):  outer loop runs 10 times, value 5 hit 5 times
        Approach 2 (set):    outer loop runs 6 times, value 5 hit 1 time

    Time:  O(n) — each unique value visited once in outer loop,
           each unique value visited at most once across all inner walks.
           Total work = 2 × unique_count <= 2n.
    Space: O(n)
*/

class Solution1 {
public:
    int longestConsecutive(vector<int>& nums) {
        int N = static_cast<int>(nums.size());

        // O(n) — deduplicate into a hash set for O(1) lookups
        unordered_set<int> hashSet(nums.begin(), nums.end());

        int sequenceLength = 0;
        int nextNumber = 0;
        int longestSequenceLength = 0;

        // BUG: iterates over the ARRAY (size N), not the SET (size <= N).
        // If nums has duplicates, the same value is visited multiple times.
        // Each duplicate that is a sequence-start triggers an identical
        // inner walk — pure wasted work.
        //
        // Example: nums = [5, 5, 5, 5, 5, 6, 7, 8, 9, 10]
        //   Outer loop runs 10 times.
        //   Value 5 is a start (4 not in set), hit 5 times.
        //   Each hit walks 5→6→7→8→9→10 (6 lookups).
        //   Total: 5 × 6 = 30 lookups just for value 5.
        for (int i = 0; i < N; i++) {

            // Check: is nums[i] the START of a consecutive sequence?
            // It's a start if (nums[i] - 1) is NOT in the set —
            // meaning nothing comes before it.
            if (hashSet.count(nums[i] - 1) == 0) {

                // Found a start. Walk forward counting consecutive elements.
                sequenceLength = 1;
                nextNumber = nums[i] + 1;

                // Extend: keep going as long as the next number exists
                while (hashSet.count(nextNumber) > 0) {
                    sequenceLength++;
                    nextNumber++;
                }

                longestSequenceLength = max(longestSequenceLength, sequenceLength);
            }
            // If nums[i] is NOT a start (its predecessor exists),
            // skip it — it'll be counted when we walk from the actual start.
        }

        return longestSequenceLength;
    }
};

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        int N = static_cast<int>(nums.size());

        // O(n) — same set construction as Approach 1
        unordered_set<int> hashSet(nums.begin(), nums.end());

        int sequenceLength = 0;
        int nextNumber = 0;
        int longestSequenceLength = 0;

        // FIX: iterate over the SET, not the array.
        // The set has only unique values → each value visited exactly once.
        // No duplicate walks, no wasted work.
        //
        // Example: nums = [5, 5, 5, 5, 5, 6, 7, 8, 9, 10]
        //   Set = {5, 6, 7, 8, 9, 10} — 6 elements.
        //   Outer loop runs 6 times. Value 5 hit once.
        //   One walk: 5→6→7→8→9→10 (6 lookups). Done.
        for (auto num : hashSet) {

            // Default: every element is at least a sequence of length 1
            sequenceLength = 1;

            // Same start-check as Approach 1, just using find() instead of count().
            // hashSet.find(num - 1) == hashSet.end()  ≡  hashSet.count(num - 1) == 0
            // Both mean: "num-1 is NOT in the set → num is a sequence start."
            if (hashSet.find(num - 1) == hashSet.end()) {

                // Walk forward from this start, same as Approach 1
                nextNumber = num + 1;
                while (hashSet.find(nextNumber) != hashSet.end()) {
                    sequenceLength++;
                    nextNumber++;
                }
            }
            // If num is NOT a start (num-1 exists), sequenceLength stays 1.
            // That 1 won't beat any real sequence, so the max is unaffected.
            longestSequenceLength = max(longestSequenceLength, sequenceLength);
        }
        return longestSequenceLength;
    }
};

int main() {
    Solution1 s1;
    Solution2 s2;

    // ---- Test with unique elements (both behave the same) ----
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << "=== Unique elements: [100, 4, 200, 1, 3, 2] ===" << endl;
    cout << "Approach 1 (array iter):  " << s1.longestConsecutive(nums1) << " (expected 4)" << endl;
    cout << "Approach 2 (set iter):    " << s2.longestConsecutive(nums1) << " (expected 4)" << endl;

    // ---- Test with duplicates (Approach 1 does redundant work) ----
    vector<int> nums2 = {1, 1, 1, 2, 3};
    cout << "\n=== Duplicates: [1, 1, 1, 2, 3] ===" << endl;
    cout << "Approach 1 (array iter):  " << s1.longestConsecutive(nums2) << " (expected 3)" << endl;
    cout << "  ^ visited value 1 three times, walked 1->2->3 each time" << endl;
    cout << "Approach 2 (set iter):    " << s2.longestConsecutive(nums2) << " (expected 3)" << endl;
    cout << "  ^ visited value 1 once, walked 1->2->3 once" << endl;

    // ---- Test with heavy duplicates ----
    vector<int> nums3 = {5, 5, 5, 5, 5, 6, 7, 8, 9, 10};
    cout << "\n=== Heavy duplicates: [5,5,5,5,5,6,7,8,9,10] ===" << endl;
    cout << "Approach 1 (array iter):  " << s1.longestConsecutive(nums3) << " (expected 6)" << endl;
    cout << "  ^ value 5 is a start, visited 5 times -> 5 walks of length 6" << endl;
    cout << "Approach 2 (set iter):    " << s2.longestConsecutive(nums3) << " (expected 6)" << endl;
    cout << "  ^ value 5 visited once -> 1 walk of length 6" << endl;

    // ---- Edge cases ----
    vector<int> nums4 = {};
    vector<int> nums5 = {7};
    vector<int> nums6 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "\n=== Edge cases ===" << endl;
    cout << "Empty:      " << s2.longestConsecutive(nums4) << " (expected 0)" << endl;
    cout << "Single [7]: " << s2.longestConsecutive(nums5) << " (expected 1)" << endl;
    cout << "[0,3,7,2,5,8,4,6,0,1]: " << s2.longestConsecutive(nums6) << " (expected 9)" << endl;

    return 0;
}
