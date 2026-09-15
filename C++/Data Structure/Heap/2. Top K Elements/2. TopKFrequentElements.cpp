#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 347 - Top K Frequent Elements

    Given an integer array `nums` and an integer `k`, return the
    k most frequent elements. You may return the answer in any order.

    Examples:
    ---------

    Example 1:
        Input:  nums = [1,1,1,2,2,3], k = 2
        Output: [1, 2]
        Explanation:
            Frequencies: 1→3, 2→2, 3→1
            Top 2 most frequent: 1 and 2.

    Example 2:
        Input:  nums = [1], k = 1
        Output: [1]

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - -10^4 <= nums[i] <= 10^4
    - k is in range [1, number of unique elements]
    - Answer is guaranteed to be unique.

    Approaches:
    ----------
    1. Sorting                   — O(n log n)
    2. Min Heap of size K        — O(n log k)
    3. Bucket Sort               — O(n)

    Approach 2 — Min Heap:
    -----------------------
    Build a frequency map. Maintain a min-heap of size k.
    For each element, if the heap has less than k items, push it.
    If the heap is full and the element's frequency > heap top,
    pop the smallest and push the new one. The heap always holds
    the k most frequent elements seen so far.

    Time: O(n + m log k), where m = number of unique elements.

    Approach 3 — Bucket Sort:
    --------------------------
    Key insight: frequencies are bounded. An element can appear
    at most n times. So we create n+1 buckets where bucket[f] =
    list of elements with frequency f.

    Then collect elements from the highest bucket downward until
    we have k elements.

    Why is the time complexity O(n) and not O(n²)?
    ------------------------------------------------
    The collection loop looks like two nested loops:

        for (int i = N; i >= 1; i--)           // outer: up to N buckets
            for (int item : bucket[i])          // inner: elements in this bucket

    But each unique element appears in exactly ONE bucket. So
    across ALL iterations of both loops, the inner loop visits
    at most m elements total (m = unique elements, m ≤ n).

    Example:
        bucket[1]: [4, 7]       ← 2 elements
        bucket[2]: [3]          ← 1 element
        bucket[3]: [1, 5, 9]   ← 3 elements
        bucket[5]: [2]          ← 1 element
        (all other buckets empty)

        Total inner loop iterations: 2 + 1 + 3 + 1 = 7 = m
        NOT n × n. Empty buckets are skipped instantly.

    So the full breakdown:
        Build frequency map:     O(n)
        Fill buckets:            O(m)
        Collect top k:           O(n + m) — walk up to n buckets, visit m elements
        Total:                   O(n)
*/

// using min heap
class Solution1 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int i : nums) {
            freq[i]++;
        }

        // Min heap {freq, element}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (auto& p : freq) {
            if(pq.size() < k){
                pq.push({p.second, p.first});
            }
            else if (pq.size() == k) {
                if (p.second > pq.top().first) {
                    pq.pop();
                    pq.push({ p.second, p.first });
                }
            }
        }

        vector<int> result;
        while(!pq.empty()){
            result.push_back(pq.top().second);
            pq.pop();
        }

        return result;
    }
};


// using bucket sort
class Solution2 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int N = nums.size();
        unordered_map<int, int> freq;
        for (int i : nums) {
            freq[i]++;
        }

        // every element can have a frequency from 1 to N
        vector<vector<int>> bucket(N + 1, vector<int>());

        for(auto &p: freq){
            int frequency = p.second;
            int element = p.first;
            bucket[frequency].push_back(element);
        }

        // collect the k elements from the bucket.
        // start from max frequency
        vector<int> result;
        bool foundKElements = false;
        
        for(int i = N; i>=1; i--){
            // collect elements from this bucket
            for(int item : bucket[i]){
                result.push_back(item);
                if(result.size() == k){
                    foundKElements = true;
                    break;
                }
            }
            if(foundKElements == true)
                break;
        }
        return result;
    }
};


int main() {
    return 0;
}
