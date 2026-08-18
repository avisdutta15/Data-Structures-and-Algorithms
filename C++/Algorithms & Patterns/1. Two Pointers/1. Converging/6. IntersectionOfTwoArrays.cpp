#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given two integer arrays nums1 and nums2, return an array of their intersection.
    Each element in the result must be UNIQUE and you may return the result in any order.

    Examples:
    ---------
    Input:  nums1 = [1, 2, 2, 1], nums2 = [2, 2]
    Output: [2]

    Input:  nums1 = [4, 9, 5], nums2 = [9, 4, 9, 8, 4]
    Output: [9, 4]  (order doesn't matter)

    Constraints:
    ------------
    - 1 <= nums1.length, nums2.length <= 1000
    - 0 <= nums1[i], nums2[i] <= 1000

    Approach 1: HashSet — O(n + m) time, O(n) space
    ---------
    - Put all elements of nums1 into a set.
    - For each element in nums2, check if it's in the set.
    - Use a result set to avoid duplicates.

    Approach 2: Sort + Two Pointers — O(nlogn + mlogm) time, O(1) extra space
    ---------
    - Sort both arrays.
    - Use two pointers (i on nums1, j on nums2).
    - If nums1[i] == nums2[j]: add to result (skip duplicates), advance both.
    - If nums1[i] < nums2[j]: advance i (need a bigger value in nums1).
    - If nums1[i] > nums2[j]: advance j (need a bigger value in nums2).

    Why two pointers work here:
    - Both arrays are sorted, so equal elements will be found when pointers align.
    - Smaller element can never match anything ahead in the other array (sorted order).

    Worked Example (Two Pointers):
    ------------------------------
    nums1 = [1, 2, 2, 1] → sorted: [1, 1, 2, 2]
    nums2 = [2, 2]       → sorted: [2, 2]

    i=0, j=0: nums1[0]=1 < nums2[0]=2, i++
    i=1, j=0: nums1[1]=1 < nums2[0]=2, i++
    i=2, j=0: nums1[2]=2 == nums2[0]=2 → add 2 to result, i++, j++
    i=3, j=1: nums1[3]=2 == nums2[1]=2 → duplicate (2 already in result), skip. i++, j++
    i=4: out of bounds, done.

    Result: [2] ✓

    Time Complexity: O(nlogn + mlogm) for sorting + O(n + m) for traversal
    Space Complexity: O(1) extra (ignoring output)
*/

// Approach 1: HashSet
class Solution1 {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> resultSet;

        for (int num : nums2) {
            if (set1.count(num)) {
                resultSet.insert(num);
            }
        }

        return vector<int>(resultSet.begin(), resultSet.end());
    }
};

// Approach 2: Sort + Two Pointers
class Solution2 {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        vector<int> result;
        int i = 0, j = 0;

        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                // Add to result only if not a duplicate
                if (result.empty() || result.back() != nums1[i]) {
                    result.push_back(nums1[i]);
                }
                i++;
                j++;
            }
            else if (nums1[i] < nums2[j]) {
                i++;
            }
            else {
                j++;
            }
        }

        return result;
    }
};

int main()
{
    Solution2 obj;
    vector<int> nums1 = {4, 9, 5};
    vector<int> nums2 = {9, 4, 9, 8, 4};

    auto result = obj.intersection(nums1, nums2);

    cout << "Intersection: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // [4, 9]

    return 0;
}
