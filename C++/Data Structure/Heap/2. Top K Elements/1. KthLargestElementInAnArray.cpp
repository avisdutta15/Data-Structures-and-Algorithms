#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    https://www.youtube.com/watch?v=ZAXSFph_L-A
    Problem Statment:
    ----------------
    Given an integer array nums and an integer k, return the kth largest element in the array.
    Note that it is the kth largest element in the sorted order, not the kth distinct element.
    Can you solve it without sorting?

    Examples:
    ---------
    Input: nums = [3,2,1,5,6,4], k = 2
    Output: 5

    Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    Output: 4

    Constraints:
    ------------
    1 <= k <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

    Approaches:
    ----------
    1. Sorting - O(nlogn)
    2. Min Heap of size K - O(nlogk)
    3. QuickSelect - O(n) average case

    Based on QuickSort's partition. Instead of sorting the whole array,
    we only recurse into the side that contains our target index.

    Kth largest = element at index (n - k) in ascending sorted order.
    After partition, the pivot is at its correct sorted position.
        - If pivot_index == target → found it, return.
        - If target < pivot_index → answer is in the left half.
        - If target > pivot_index → answer is in the right half.

    Only one side is explored each time → O(n) average (not O(n log n)).

    How Partition Works:
    --------------------
    We pick a pivot and rearrange the array so that:
        - Everything LEFT  of the pivot is < pivot
        - Everything RIGHT of the pivot is >= pivot
        - The pivot is at its final sorted position

    We use two pointers:
        i = boundary between "< pivot" and ">= pivot" regions
        j = scanner that walks left to right

    Array layout during partition:

        [  < pivot        |  >= pivot       |    unseen         | pivot ]
         low ... i-1        i ... j-1         j ... high-1         high

        nums[low..i-1]    → all < pivot     (processed, smaller)
        nums[i..j-1]      → all >= pivot    (processed, larger or equal)
        nums[j..high-1]   → not yet scanned
        nums[high]        → pivot itself

    nums[i] is always the FIRST element in the ">= pivot" region.
    When j finds a smaller element, swap nums[j] with nums[i] —
    this pushes the small element into the left region.

    After the loop, swap nums[i] with nums[high] to place the pivot
    at index i — its correct sorted position.


    Array Layout:
    -------------
    1. During partition

        [  < pivot        |  >= pivot       |    unseen         | pivot ]
         low ... i-1        i ... j-1         j ... high-1         high

    2. After loop finishes

        [ < pivot   |     >=pivot       |   pivot ]
         low...i-1       i..high-1           high     

    3. Last swap. i...high-1 has elements >= pivot. but pivot is at high
       To make all the elements from i....high >=pivot, swap A[i] and A[high]
       bringing pivot at ith position.

        [ < pivot   |     pivot         |   >=pivot ]
         low...i-1          i              i+1...high     

    Why >=pivot
      [i+1..high]

    Because nums[i+1..high] could contain elements equal to pivot too (not just strictly greater)

    Dry Run:
    --------
    nums = [7, 2, 5, 3, 6], pivot = 6 (at high)

    j=0: nums[0]=7, 7 >= 6 → skip         [7, 2, 5, 3, 6]  i=0
    j=1: nums[1]=2, 2 <  6 → swap(0,1)    [2, 7, 5, 3, 6]  i=1
    j=2: nums[2]=5, 5 <  6 → swap(1,2)    [2, 5, 7, 3, 6]  i=2
    j=3: nums[3]=3, 3 <  6 → swap(2,3)    [2, 5, 3, 7, 6]  i=3

    End: swap(i=3, high=4)                 [2, 5, 3, 6, 7]
                                                    ^
                                            pivot at index 3 (sorted position)

    Left of 6:  [2, 5, 3] — all < 6  ✓
    Right of 6: [7]        — all >= 6 ✓

    Random Pivot Optimization:
    --------------------------
    Always picking nums[high] as pivot gives O(n²) on sorted input
    (each partition only removes 1 element). Picking a random pivot
    makes this astronomically unlikely → O(n) average.

    Complexity:
    -----------
    Time:  O(n) average, O(n²) worst (with random pivot, worst is rare)
    Space: O(log n) average for recursion stack
*/

class Solution1 {
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size()-k];
    }
};

class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> PQ;

        for (int i : nums) {
            if(PQ.size() < k) PQ.push(i);
            else if (PQ.size() == k) {
                if (i > PQ.top()) {
                    PQ.pop();
                    PQ.push(i);
                }
            }
        }

        return PQ.top();
    }
};

// Quick Select Approach
class Solution3 {
private:
    int partition(vector<int>& nums, int low, int high) {
        // Pick a random pivot and move it to the end.
        // This avoids O(n²) worst case on sorted input.
        int randomIndex = low + rand() % (high - low + 1);
        swap(nums[randomIndex], nums[high]);

        // Pivot is now at nums[high]
        int pivot = nums[high];

        // i = boundary: everything before i is < pivot
        // j = scanner: walks through the array left to right
        int i = low;

        for (int j = low; j < high; j++) {
            // If current element is smaller than pivot,
            // swap it to the "less than" region and advance boundary
            if (nums[j] < pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
            // If nums[j] >= pivot, just move j forward (element stays in place)
        }

        // Place pivot at its correct sorted position (index i)
        // After this: nums[low..i-1] < pivot, nums[i] = pivot, nums[i+1..high] >= pivot
        swap(nums[i], nums[high]);
        return i;
    }
    int quickSelect(vector<int>& nums, int low, int high, int k) {
        if(low == high) 
            return nums[low];

        // partition the array around a pivot
        int pivot_index = partition(nums, low, high);

        // check if the pivot is the kth largest element
        if(pivot_index == k)
            return nums[pivot_index];
        else if( k < pivot_index)
            // search in the left subarray
            return quickSelect(nums, low, pivot_index-1, k);
        else
            // search in the right subarray
            return quickSelect(nums, pivot_index+1, high, k);
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int low = 0;
        int high = nums.size() - 1;
        k = nums.size() - k;        // kth largest means N-K the index element after sorted
        return quickSelect(nums, low, high, k);
    }
};

int main() {
    return 0;
}
