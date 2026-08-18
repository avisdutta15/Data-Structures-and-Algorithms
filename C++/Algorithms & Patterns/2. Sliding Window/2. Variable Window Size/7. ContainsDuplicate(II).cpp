#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Contains Duplicate II (LeetCode 219)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given an integer array nums and an integer k, return true if there are two
    distinct indices i and j in the array such that:
        - nums[i] == nums[j]
        - abs(i - j) <= k

    Examples:
    ---------
    Input:  nums = [1, 2, 3, 1], k = 3
    Output: true
    Explanation: nums[0] == nums[3], and abs(0-3) = 3 <= 3.

    Input:  nums = [1, 0, 1, 1], k = 1
    Output: true
    Explanation: nums[2] == nums[3], and abs(2-3) = 1 <= 1.

    Input:  nums = [1, 2, 3, 1, 2, 3], k = 2
    Output: false
    Explanation: Closest duplicates are 3 apart (indices 0,3 or 1,4 or 2,5). 3 > 2.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - -10^9 <= nums[i] <= 10^9
    - 0 <= k <= 10^5

    Approach 1: HashMap (last index) — O(N) time, O(N) space
    ---------
    Store the last seen index of each value. When we see a value again, check if
    current_index - last_index <= k.

    Approach 2: Sliding Window with HashSet — O(N) time, O(k) space
    ---------
    Maintain a window (set) of size at most k. The window represents the last k elements.
    - Expand: try to insert nums[right] into the set.
      - If it's already in the set → duplicate within distance k → return true.
    - If window size exceeds k: shrink by removing nums[left] from set. left++.

    This is essentially a FIXED-SIZE window of size k+1 (at most k+1 elements),
    checking for duplicates within that window.

    Why this works:
    - The set always contains elements within index distance k of each other.
    - If nums[right] is already in the set, there's a duplicate within range.
    - By removing nums[left] when the window gets too big, we ensure we only
      look at elements within distance k.

    Worked Example (Approach 2):
    ----------------------------
    nums = [1, 2, 3, 1], k = 3

    left=0, right=0: set={}. 1 not in set. Insert. set={1}. window size=1 <= 3+1.
    left=0, right=1: set={1}. 2 not in set. Insert. set={1,2}. window size=2 <= 4.
    left=0, right=2: set={1,2}. 3 not in set. Insert. set={1,2,3}. window size=3 <= 4.
    left=0, right=3: set={1,2,3}. 1 IS in set! → return true ✓

    Another: nums = [1, 2, 3, 1, 2, 3], k = 2

    left=0, right=0: 1 not in set. set={1}.
    left=0, right=1: 2 not in set. set={1,2}.
    left=0, right=2: 3 not in set. set={1,2,3}. size=3 > k+1=3? No (3 == 3). OK.
                     Actually window should be at most k+1 = 3 elements. size=3 is fine.
    left=0, right=3: 1 IS in set? Yes! But wait, abs(0-3)=3 > k=2. Hmm.
                     Actually we need to shrink FIRST if window > k.
                     Window size before insert = 3. We're about to add right=3.
                     If we keep window size = k+1 = 3, we remove left=0 first.
                     Remove nums[0]=1. set={2,3}. left=1.
                     Now check: 1 not in set. Insert. set={2,3,1}.
    left=1, right=4: Remove nums[1]=2. set={3,1}. left=2.
                     2 not in set. Insert. set={3,1,2}.
    left=2, right=5: Remove nums[2]=3. set={1,2}. left=3.
                     3 not in set. Insert. set={1,2,3}.
    Done. Return false ✓

    Time Complexity: O(N)
    Space Complexity: O(min(N, k)) for the set
*/

// ── Approach 1: HashMap (last seen index) ──
class Solution1 {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> lastSeen;  // value → last index

        for (int i = 0; i < nums.size(); i++) {
            // If we've seen this value before and it's within distance k
            if (lastSeen.count(nums[i]) > 0 && i - lastSeen[nums[i]] <= k) {
                return true;
            }
            // Update last seen index
            lastSeen[nums[i]] = i;
        }

        return false;
    }
};

// ── Approach 2: Sliding Window with HashSet ──
class Solution2 {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> window;  // elements in current window of size <= k

        int left = 0, right = 0;

        while (right < (int)nums.size()) {
            // If window has more than k elements, shrink from left
            if (right - left > k) {
                window.erase(nums[left]);
                left++;
            }

            // Check if nums[right] already exists in window (duplicate within k)
            if (window.count(nums[right])) {
                return true;
            }

            // Add nums[right] to window
            window.insert(nums[right]);
            right++;
        }

        return false;
    }
};

int main()
{
    Solution1 sol1;
    Solution2 sol2;

    vector<int> nums1 = {1, 2, 3, 1};
    cout << "HashMap: " << (sol1.containsNearbyDuplicate(nums1, 3) ? "true" : "false") << endl;  // true
    cout << "Window:  " << (sol2.containsNearbyDuplicate(nums1, 3) ? "true" : "false") << endl;  // true

    vector<int> nums2 = {1, 2, 3, 1, 2, 3};
    cout << "HashMap: " << (sol1.containsNearbyDuplicate(nums2, 2) ? "true" : "false") << endl;  // false
    cout << "Window:  " << (sol2.containsNearbyDuplicate(nums2, 2) ? "true" : "false") << endl;  // false

    return 0;
}
